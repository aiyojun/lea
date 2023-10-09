// Generated from C:/Users/jun.dai/Documents/GitHub/lea/grammar/ScriptGrammar.g4 by ANTLR 4.13.1

import {ParseTreeListener} from "antlr4";


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
 * This interface defines a complete listener for a parse tree produced by
 * `ScriptGrammarParser`.
 */
export default class ScriptGrammarListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.program`.
	 * @param ctx the parse tree
	 */
	enterProgram?: (ctx: ProgramContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.program`.
	 * @param ctx the parse tree
	 */
	exitProgram?: (ctx: ProgramContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.declarations`.
	 * @param ctx the parse tree
	 */
	enterDeclarations?: (ctx: DeclarationsContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.declarations`.
	 * @param ctx the parse tree
	 */
	exitDeclarations?: (ctx: DeclarationsContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.classDeclaration`.
	 * @param ctx the parse tree
	 */
	enterClassDeclaration?: (ctx: ClassDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.classDeclaration`.
	 * @param ctx the parse tree
	 */
	exitClassDeclaration?: (ctx: ClassDeclarationContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.members`.
	 * @param ctx the parse tree
	 */
	enterMembers?: (ctx: MembersContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.members`.
	 * @param ctx the parse tree
	 */
	exitMembers?: (ctx: MembersContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.member`.
	 * @param ctx the parse tree
	 */
	enterMember?: (ctx: MemberContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.member`.
	 * @param ctx the parse tree
	 */
	exitMember?: (ctx: MemberContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.variableDeclaration`.
	 * @param ctx the parse tree
	 */
	enterVariableDeclaration?: (ctx: VariableDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.variableDeclaration`.
	 * @param ctx the parse tree
	 */
	exitVariableDeclaration?: (ctx: VariableDeclarationContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.functionDeclaration`.
	 * @param ctx the parse tree
	 */
	enterFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.functionDeclaration`.
	 * @param ctx the parse tree
	 */
	exitFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.params`.
	 * @param ctx the parse tree
	 */
	enterParams?: (ctx: ParamsContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.params`.
	 * @param ctx the parse tree
	 */
	exitParams?: (ctx: ParamsContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.statements`.
	 * @param ctx the parse tree
	 */
	enterStatements?: (ctx: StatementsContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.statements`.
	 * @param ctx the parse tree
	 */
	exitStatements?: (ctx: StatementsContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.blockStatement`.
	 * @param ctx the parse tree
	 */
	enterBlockStatement?: (ctx: BlockStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.blockStatement`.
	 * @param ctx the parse tree
	 */
	exitBlockStatement?: (ctx: BlockStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.ifStatement`.
	 * @param ctx the parse tree
	 */
	enterIfStatement?: (ctx: IfStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.ifStatement`.
	 * @param ctx the parse tree
	 */
	exitIfStatement?: (ctx: IfStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.multiIfStatement`.
	 * @param ctx the parse tree
	 */
	enterMultiIfStatement?: (ctx: MultiIfStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.multiIfStatement`.
	 * @param ctx the parse tree
	 */
	exitMultiIfStatement?: (ctx: MultiIfStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.elseStatement`.
	 * @param ctx the parse tree
	 */
	enterElseStatement?: (ctx: ElseStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.elseStatement`.
	 * @param ctx the parse tree
	 */
	exitElseStatement?: (ctx: ElseStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.forStatement`.
	 * @param ctx the parse tree
	 */
	enterForStatement?: (ctx: ForStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.forStatement`.
	 * @param ctx the parse tree
	 */
	exitForStatement?: (ctx: ForStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.whileStatement`.
	 * @param ctx the parse tree
	 */
	enterWhileStatement?: (ctx: WhileStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.whileStatement`.
	 * @param ctx the parse tree
	 */
	exitWhileStatement?: (ctx: WhileStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.returnStatement`.
	 * @param ctx the parse tree
	 */
	enterReturnStatement?: (ctx: ReturnStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.returnStatement`.
	 * @param ctx the parse tree
	 */
	exitReturnStatement?: (ctx: ReturnStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.continueStatement`.
	 * @param ctx the parse tree
	 */
	enterContinueStatement?: (ctx: ContinueStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.continueStatement`.
	 * @param ctx the parse tree
	 */
	exitContinueStatement?: (ctx: ContinueStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.breakStatement`.
	 * @param ctx the parse tree
	 */
	enterBreakStatement?: (ctx: BreakStatementContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.breakStatement`.
	 * @param ctx the parse tree
	 */
	exitBreakStatement?: (ctx: BreakStatementContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.expression`.
	 * @param ctx the parse tree
	 */
	enterExpression?: (ctx: ExpressionContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.expression`.
	 * @param ctx the parse tree
	 */
	exitExpression?: (ctx: ExpressionContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.accessExpression`.
	 * @param ctx the parse tree
	 */
	enterAccessExpression?: (ctx: AccessExpressionContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.accessExpression`.
	 * @param ctx the parse tree
	 */
	exitAccessExpression?: (ctx: AccessExpressionContext) => void;
	/**
	 * Enter a parse tree produced by `ScriptGrammarParser.arguments`.
	 * @param ctx the parse tree
	 */
	enterArguments?: (ctx: ArgumentsContext) => void;
	/**
	 * Exit a parse tree produced by `ScriptGrammarParser.arguments`.
	 * @param ctx the parse tree
	 */
	exitArguments?: (ctx: ArgumentsContext) => void;
}

