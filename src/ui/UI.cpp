#include "UI.h"

#include "dom/Root.h"

#include "scene/Scene.h"
#include "engine/Engine.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "Class.h"
#include "gse/ExecutionPointer.h"
#include "gc/Space.h"

namespace ui {

UI::UI( GSE_CALLABLE )
	: gse::GCWrappable( gc_space )
	, m_gc_space( gc_space )
	, m_scene(new scene::Scene( "Scene::UI", scene::SCENE_TYPE_UI ) ){

	m_clamp.x.SetRange(
		{
			{ 0.0,  (float)g_engine->GetGraphics()->GetViewportWidth() },
			{ -1.0, 1.0 }
		}
	);
	m_clamp.x.SetOverflowAllowed( true );

	m_clamp.y.SetRange(
		{
			{ 0.0,  (float)g_engine->GetGraphics()->GetViewportHeight() },
			{ -1.0, 1.0 }
		}
	);
	m_clamp.y.SetOverflowAllowed( true );
	m_clamp.y.SetInversed( true );

	g_engine->GetGraphics()->AddOnWindowResizeHandler(
		this, RH( this ) {
			Resize();
		}
	);

	g_engine->GetGraphics()->AddScene( m_scene );
	m_root = new dom::Root( GSE_CALL, this );
	Resize();

	g_engine->GetInput()->AddHandler( this, [ this, gc_space, ctx, si ]( const input::Event& event ){
		if ( event.type == input::EV_MOUSE_MOVE ) {
			m_last_mouse_position = {
				event.data.mouse.x,
				event.data.mouse.y
			};
		}
		m_gc_space->Accumulate( [ this, &ctx, &gc_space, &si, &event ] () {
			gse::ExecutionPointer ep;
			m_root->ProcessEvent( GSE_CALL, event );
		});
	});
}

UI::~UI() {

	g_engine->GetInput()->RemoveHandler( this );

	g_engine->GetGraphics()->RemoveScene( m_scene );
	delete m_scene;

	g_engine->GetGraphics()->RemoveOnWindowResizeHandler( this );

}

void UI::Iterate() {
	for ( const auto& it : m_iterables ) {
		it.second();
	}
}

WRAPIMPL_BEGIN( UI )
	WRAPIMPL_PROPS
	WRAPIMPL_TRIGGERS
			{
				"root",
				m_root->Wrap( GSE_CALL, true )
			},
			{
				"class",
				NATIVE_CALL( this ) {
					N_EXPECT_ARGS_MIN_MAX( 1, 3 ); // .class(name) or .class(name, properties) or .class(name, parent) or .class(name, parent, properties)
					N_GETVALUE( name, 0, String );
					auto it = m_classes.find( name );
					if ( it == m_classes.end() ) {
						Log( "Creating UI class: " + name );
						it = m_classes.insert({ name, new ui::Class( gc_space, this, name ) }).first;
						if ( arguments.size() >= 2 ) {
							const gse::value::object_properties_t* properties = nullptr;
							const std::string* parent_class = nullptr;
							if ( arguments.size() == 2 ) {
								if ( arguments.at(1)->type == gse::Value::T_STRING ) {
									N_GETVALUE( s, 1, String );
									parent_class = &s;
								}
								else {
									N_GETVALUE( p, 1, Object );
									properties = &p;
								}
							}
							else {
								N_GETVALUE( s, 1, String );
								N_GETVALUE( p, 2, Object );
								parent_class = &s;
								properties = &p;
							}
							if ( parent_class ) {
								it->second->SetParentClass( GSE_CALL, *parent_class );
							}
							if ( properties ) {
								it->second->SetProperties( GSE_CALL, *properties );
							}
						}
					}
					else if ( arguments.size() >= 2 ) {
						// passing parent class or properties in constructor works only if class didn't exist yet
						GSE_ERROR( gse::EC.UI_ERROR, "Class '" + name + "' already exists. Use .set() instead of constructor to update properties of existing classes." );
					}
					return it->second->Wrap( GSE_CALL, true );
				} )
			},
		};
WRAPIMPL_END_PTR()

void UI::Resize() {
	const auto& g = g_engine->GetGraphics();
/*#ifdef DEBUG
			for ( auto& it : m_debug_frames ) {
				ResizeDebugFrame( it.first, &it.second );
			}
#endif*/
	m_clamp.x.SetSrcRange(
		{
			0.0,
			(float)g->GetViewportWidth()
		}
	);
	m_clamp.y.SetSrcRange(
		{
			0.0,
			(float)g->GetViewportHeight()
		}
	);
	m_root->Resize( g->GetViewportWidth(), g->GetViewportHeight() );
}

const types::mesh::coord_t UI::ClampX( const coord_t& x ) const {
	return m_clamp.x.Clamp( x );
}

const types::mesh::coord_t UI::ClampY( const coord_t& y ) const {
	return m_clamp.y.Clamp( y );
}

const types::Vec2< types::mesh::coord_t > UI::ClampXY( const types::Vec2< coord_t >& xy ) const {
	return {
		m_clamp.x.Clamp( xy.x ),
		m_clamp.y.Clamp( xy.y ),
	};
}

ui::Class* const UI::GetClass( const std::string& name ) const {
	const auto& it = m_classes.find( name );
	if ( it != m_classes.end() ) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

const types::Vec2< ssize_t >& UI::GetLastMousePosition() const {
	return m_last_mouse_position;
}

void UI::Destroy( GSE_CALLABLE ) {
	m_root->Destroy( GSE_CALL );
}

void UI::GetReachableObjects( std::unordered_set< gc::Object* >& reachable_objects ) {
	gse::GCWrappable::GetReachableObjects( reachable_objects );

	GC_DEBUG_BEGIN( "UI" );

	GC_REACHABLE( m_root );

	GC_DEBUG_BEGIN( "classes" );
	for ( const auto& it : m_classes ) {
		GC_REACHABLE( it.second );
	}
	GC_DEBUG_END();

	GC_DEBUG_END();
}

void UI::AddIterable( const dom::Object* const obj, const f_iterable_t& f ) {
	ASSERT( m_iterables.find( obj ) == m_iterables.end(), "iterable already exists" );
	m_iterables.insert( {obj, f } );
}

void UI::RemoveIterable( const dom::Object* const obj ) {
	ASSERT( m_iterables.find( obj ) != m_iterables.end(), "iterable not found" );
	m_iterables.erase( obj );
}

gc::Space* const UI::GetGCSpace() const {
	return m_gc_space;
}

}
