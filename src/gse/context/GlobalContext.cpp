#include "GlobalContext.h"

#include "util/FS.h"
#include "util/String.h"

#include "gse/GSE.h"

namespace gse {
namespace context {

GlobalContext::GlobalContext( GSE* gse, const std::string& source_path )
	: Context( gse )
	, m_script_info(
		{
			source_path,
			util::FS::GetBaseName( source_path, GSE::PATH_SEPARATOR ),
			util::FS::GetDirName( source_path, GSE::PATH_SEPARATOR ),
		}
	)
	, m_source_lines(
		source_path.empty()
			? source_lines_t{}
			: util::String::Split( util::FS::ReadTextFile( source_path, GSE::PATH_SEPARATOR ), '\n' )
	) {}

Context* GlobalContext::GetParentContext() const {
	return nullptr;
}

const bool GlobalContext::IsTraceable() const {
	return false;
}

static const std::string s_empty = "";
const std::string& GlobalContext::GetSourceLine( const size_t line_num ) const {
	if ( line_num == 0 ) {
		return s_empty;
	}
	ASSERT_NOLOG( line_num <= m_source_lines.size(), "source line overflow" );
	return m_source_lines.at( line_num - 1 );
}

static const si_t s_empty_si = {};
const si_t& GlobalContext::GetSI() const {
	//THROW( "global contexts are not supposed to have si" ); // for some reason this gets thrown at Release builds but not Debug
	return s_empty_si;
}

const Context::script_info_t& GlobalContext::GetScriptInfo() const {
	return m_script_info;
}

void GlobalContext::AddSourceLine( const std::string& source_line ) {
	m_source_lines.push_back( source_line );
}

void GlobalContext::AddSourceLines( const source_lines_t& source_lines ) {
	m_source_lines.insert( m_source_lines.begin(), source_lines.begin(), source_lines.end() );
}

}
}
