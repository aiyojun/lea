// Generated from C:/Users/jun.dai/Documents/GitHub/lea/grammar/ScriptGrammar.g4 by ANTLR 4.13.1

import {ParseTreeVisitor} from 'antlr4';


import { ProgramContext } from "./ScriptGrammarParser";
import { DeclarationsContext } from "./ScriptGrammarParser";
import { ClassDeclarationContext } from "./ScriptGrammarParser";
import { MembersContext } from "./ScriptGrammarParser";
import { MemberContext } from "./ScriptGrammarParser";
import { VariableDeclarationContext } from "./ScriptGrammarParser";
import { FunctionDeclarationContext } from "./ScriptGrammarParser";
import { ParamsContext } from "./ScriptGrammarParser";
import { StatementsContext } from "./ScriptGrammarParser";
import { BlockStatementContext } from "./ScriptGrammarParser";
import { IfStatementContext } from "./ScriptGrammarParser";
import { MultiIfStatementContext } from "./ScriptGrammarParser";
import { ElseStatementContext } from "./ScriptGrammarParser";
import { ForStatementContext } from "./ScriptGrammarParser";
import { WhileStatementContext } from "./ScriptGrammarParser";
import { ReturnStatementContext } from "./ScriptGrammarParser";
import { ContinueStatementContext } from "./ScriptGrammarParser";
import { BreakStatementContext } from "./ScriptGrammarParser";
import { ExpressionContext } from "./ScriptGrammarParser";
import { AccessExpressionContext } from "./ScriptGrammarParser";
import { ArgumentsContext } from "./ScriptGrammarParser";


/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by `ScriptGrammarParser`.
 *
 * @param <Result> The return type of the visit operation. Use `void` for
 * operations with no return type.
 */
export default class ScriptGrammarVisitor<Result> extends ParseTreeVisitor<Result> {
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.program`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitProgram?: (ctx: ProgramContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.declarations`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitDeclarations?: (ctx: DeclarationsContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.classDeclaration`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitClassDeclaration?: (ctx: ClassDeclarationContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.members`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitMembers?: (ctx: MembersContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.member`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitMember?: (ctx: MemberContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.variableDeclaration`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitVariableDeclaration?: (ctx: VariableDeclarationContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.functionDeclaration`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitFunctionDeclaration?: (ctx: FunctionDeclarationContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.params`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitParams?: (ctx: ParamsContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.statements`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitStatements?: (ctx: StatementsContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.blockStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitBlockStatement?: (ctx: BlockStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.ifStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitIfStatement?: (ctx: IfStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.multiIfStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitMultiIfStatement?: (ctx: MultiIfStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.elseStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitElseStatement?: (ctx: ElseStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.forStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitForStatement?: (ctx: ForStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.whileStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitWhileStatement?: (ctx: WhileStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.returnStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitReturnStatement?: (ctx: ReturnStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.continueStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitContinueStatement?: (ctx: ContinueStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.breakStatement`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitBreakStatement?: (ctx: BreakStatementContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.expression`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitExpression?: (ctx: ExpressionContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.accessExpression`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitAccessExpression?: (ctx: AccessExpressionContext) => Result;
	/**
	 * Visit a parse tree produced by `ScriptGrammarParser.arguments`.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	visitArguments?: (ctx: ArgumentsContext) => Result;
}

