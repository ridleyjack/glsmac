#pragma once

#include <string>
#include <optional>

#include "Runner.h"

#include "gse/value/Types.h"

#include "gse/value/Callable.h"

namespace gse {

namespace program {
class Scope;
class Statement;
class Control;
class Conditional;
class Expression;
class Operand;
class Variable;
}

namespace value {
class Array;
}

namespace runner {

CLASS( Interpreter, Runner )

	Interpreter( gc::Space* const gc_space );

	Value* const Execute( context::Context* ctx, ExecutionPointer& ep, const program::Program* program ) override;

private:

	// TODO: make it multithreaded
	std::recursive_mutex m_execute_mutex;

	class Function : public value::Callable {
	public:
		Function(
			gc::Space* const gc_space,
			Interpreter* runner,
			context::Context* context,
			const std::vector< std::string >& parameters,
			const program::Program* const program
		);
		~Function();
		void GetReachableObjects( std::unordered_set< gc::Object* >& reachable_objects ) override;
		Value* Run( GSE_CALLABLE, const value::function_arguments_t& arguments ) override;
	private:
		Interpreter* runner;
		context::Context* context;
		const std::vector< std::string > parameters;
		const program::Program* const program;
	};

	Value* const EvaluateScope( context::Context* ctx, ExecutionPointer& ep, const program::Scope* scope, bool* returnflag = nullptr );
	Value* const EvaluateStatement( context::Context* ctx, ExecutionPointer& ep, const program::Statement* statement, bool* returnflag = nullptr );
	Value* const EvaluateConditional( context::Context* ctx, ExecutionPointer& ep, const program::Conditional* conditional, bool is_nested, bool* returnflag = nullptr );
	Value* const EvaluateExpression( context::Context* ctx, ExecutionPointer& ep, const program::Expression* expression, bool* returnflag = nullptr );
	Value* const EvaluateOperand( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand );
	const std::string EvaluateString( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand );
	Value* const EvaluateRange( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand, const bool only_index = false );
	const bool EvaluateBool( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand );
	const program::Variable* EvaluateVariable( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand );
	const std::string EvaluateVarName( context::Context* ctx, ExecutionPointer& ep, const program::Operand* operand );

	Value* const Deref( context::Context* ctx, const si_t& si, ExecutionPointer& ep, Value* const value );
	void WriteByRef( context::Context* ctx, const si_t& si, ExecutionPointer& ep, Value* const ref, Value* const value );
	void ValidateRange( context::Context* ctx, const si_t& si, ExecutionPointer& ep, const value::Array* array, const std::optional< size_t > from, const std::optional< size_t > to );
	void CheckBreakCondition( gse::Value* const result, bool* need_break, bool* need_clear );

};

}
}
