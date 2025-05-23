#pragma once

#include <map>
#include <string>
#include <functional>
#include <unordered_set>

#include "gse/Value.h"

#include "Types.h"
#include "gse/Types.h"
#include "gse/ExecutionPointer.h"

namespace gse {

class Wrappable;

namespace context {
class Context;

class ChildContext;
}

namespace value {

class Object : public Value {
public:

	// internal use only for now
	typedef std::string object_class_t;

	static const type_t GetType() { return Value::T_OBJECT; }

	typedef void (wrapsetter_t)( Wrappable*, const std::string&, Value* const, GSE_CALLABLE ); // ( obj, key, value, GSE_CALL )
	Object( GSE_CALLABLE, object_properties_t initial_value = {}, const object_class_t object_class = "", Wrappable* wrapobj = nullptr, wrapsetter_t* wrapsetter = nullptr );
	~Object();

	Value* const Get( const object_key_t& key );
	void Assign( const object_key_t& key, Value* const new_value, const std::function< void() >& f_on_set = nullptr );
	void Set( const object_key_t& key, Value* const new_value, GSE_CALLABLE );

	const object_properties_t& value = m_value;

	Value* const GetRef( const object_key_t& key );

	void Unlink();

	void GetReachableObjects( std::unordered_set< gc::Object* >& reachable_objects ) override;

	const object_class_t object_class;
	Wrappable* wrapobj;
	wrapsetter_t* wrapsetter;

	context::ChildContext* const GetContext() const;

	friend class gse::Value; // to be able to copy objects
	context::ChildContext* m_ctx = nullptr;
	const si_t m_si = {};
	const gse::ExecutionPointer m_ep = {};

private:
	Value* m_this = nullptr;

	object_properties_t m_value = {};

};

}
}
