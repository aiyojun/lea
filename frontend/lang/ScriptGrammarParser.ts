// Generated from C:/Users/jun.dai/Documents/GitHub/lea/grammar/ScriptGrammar.g4 by ANTLR 4.13.1
// noinspection ES6UnusedImports,JSUnusedGlobalSymbols,JSUnusedLocalSymbols

import {
	ATN,
	ATNDeserializer, DecisionState, DFA, FailedPredicateException,
	RecognitionException, NoViableAltException, BailErrorStrategy,
	Parser, ParserATNSimulator,
	RuleContext, ParserRuleContext, PredictionMode, PredictionContextCache,
	TerminalNode, RuleNode,
	Token, TokenStream,
	Interval, IntervalSet
} from 'antlr4';
import ScriptGrammarListener from "./ScriptGrammarListener.js";
import ScriptGrammarVisitor from "./ScriptGrammarVisitor.js";

// for running tests with parameters, TODO: discuss strategy for typed parameters in CI
// eslint-disable-next-line no-unused-vars
type int = number;

export default class ScriptGrammarParser extends Parser {
	public static readonly T__0 = 1;
	public static readonly T__1 = 2;
	public static readonly T__2 = 3;
	public static readonly T__3 = 4;
	public static readonly T__4 = 5;
	public static readonly T__5 = 6;
	public static readonly T__6 = 7;
	public static readonly T__7 = 8;
	public static readonly T__8 = 9;
	public static readonly T__9 = 10;
	public static readonly T__10 = 11;
	public static readonly T__11 = 12;
	public static readonly T__12 = 13;
	public static readonly T__13 = 14;
	public static readonly T__14 = 15;
	public static readonly T__15 = 16;
	public static readonly T__16 = 17;
	public static readonly T__17 = 18;
	public static readonly T__18 = 19;
	public static readonly T__19 = 20;
	public static readonly T__20 = 21;
	public static readonly T__21 = 22;
	public static readonly T__22 = 23;
	public static readonly T__23 = 24;
	public static readonly T__24 = 25;
	public static readonly T__25 = 26;
	public static readonly T__26 = 27;
	public static readonly T__27 = 28;
	public static readonly T__28 = 29;
	public static readonly T__29 = 30;
	public static readonly T__30 = 31;
	public static readonly T__31 = 32;
	public static readonly T__32 = 33;
	public static readonly T__33 = 34;
	public static readonly T__34 = 35;
	public static readonly T__35 = 36;
	public static readonly T__36 = 37;
	public static readonly T__37 = 38;
	public static readonly T__38 = 39;
	public static readonly T__39 = 40;
	public static readonly T__40 = 41;
	public static readonly T__41 = 42;
	public static readonly T__42 = 43;
	public static readonly T__43 = 44;
	public static readonly T__44 = 45;
	public static readonly T__45 = 46;
	public static readonly T__46 = 47;
	public static readonly T__47 = 48;
	public static readonly WS = 49;
	public static readonly SEMI = 50;
	public static readonly NUMBER = 51;
	public static readonly HEX = 52;
	public static readonly OCT = 53;
	public static readonly BIN = 54;
	public static readonly ID = 55;
	public static readonly STRING = 56;
	public static readonly BLOCK_COMMENT = 57;
	public static readonly LINE_COMMENT = 58;
	public static readonly EOF = Token.EOF;
	public static readonly RULE_program = 0;
	public static readonly RULE_declarations = 1;
	public static readonly RULE_classDeclaration = 2;
	public static readonly RULE_members = 3;
	public static readonly RULE_member = 4;
	public static readonly RULE_variableDeclaration = 5;
	public static readonly RULE_functionDeclaration = 6;
	public static readonly RULE_params = 7;
	public static readonly RULE_statements = 8;
	public static readonly RULE_blockStatement = 9;
	public static readonly RULE_ifStatement = 10;
	public static readonly RULE_multiIfStatement = 11;
	public static readonly RULE_elseStatement = 12;
	public static readonly RULE_forStatement = 13;
	public static readonly RULE_whileStatement = 14;
	public static readonly RULE_returnStatement = 15;
	public static readonly RULE_continueStatement = 16;
	public static readonly RULE_breakStatement = 17;
	public static readonly RULE_expression = 18;
	public static readonly RULE_accessExpression = 19;
	public static readonly RULE_arguments = 20;
	public static readonly literalNames: (string | null)[] = [ null, "'class'", 
                                                            "'extend'", 
                                                            "'{'", "'}'", 
                                                            "'private'", 
                                                            "'protected'", 
                                                            "'public'", 
                                                            "'static'", 
                                                            "'='", "'def'", 
                                                            "'('", "')'", 
                                                            "','", "'else'", 
                                                            "'if'", "'for'", 
                                                            "'in'", "'while'", 
                                                            "'return'", 
                                                            "'continue'", 
                                                            "'break'", "'!'", 
                                                            "'~'", "'+'", 
                                                            "'-'", "'*'", 
                                                            "'/'", "'%'", 
                                                            "'>='", "'<='", 
                                                            "'>'", "'<'", 
                                                            "'=='", "'!='", 
                                                            "'&'", "'^'", 
                                                            "'|'", "'&&'", 
                                                            "'||'", "'?'", 
                                                            "':'", "'new'", 
                                                            "'true'", "'false'", 
                                                            "'null'", "'['", 
                                                            "']'", "'.'", 
                                                            null, "';'" ];
	public static readonly symbolicNames: (string | null)[] = [ null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, null, 
                                                             null, "WS", 
                                                             "SEMI", "NUMBER", 
                                                             "HEX", "OCT", 
                                                             "BIN", "ID", 
                                                             "STRING", "BLOCK_COMMENT", 
                                                             "LINE_COMMENT" ];
	// tslint:disable:no-trailing-whitespace
	public static readonly ruleNames: string[] = [
		"program", "declarations", "classDeclaration", "members", "member", "variableDeclaration", 
		"functionDeclaration", "params", "statements", "blockStatement", "ifStatement", 
		"multiIfStatement", "elseStatement", "forStatement", "whileStatement", 
		"returnStatement", "continueStatement", "breakStatement", "expression", 
		"accessExpression", "arguments",
	];
	public get grammarFileName(): string { return "ScriptGrammar.g4"; }
	public get literalNames(): (string | null)[] { return ScriptGrammarParser.literalNames; }
	public get symbolicNames(): (string | null)[] { return ScriptGrammarParser.symbolicNames; }
	public get ruleNames(): string[] { return ScriptGrammarParser.ruleNames; }
	public get serializedATN(): number[] { return ScriptGrammarParser._serializedATN; }

	protected createFailedPredicateException(predicate?: string, message?: string): FailedPredicateException {
		return new FailedPredicateException(this, predicate, message);
	}

	constructor(input: TokenStream) {
		super(input);
		this._interp = new ParserATNSimulator(this, ScriptGrammarParser._ATN, ScriptGrammarParser.DecisionsToDFA, new PredictionContextCache());
	}
	// @RuleVersion(0)
	public program(): ProgramContext {
		let localctx: ProgramContext = new ProgramContext(this, this._ctx, this.state);
		this.enterRule(localctx, 0, ScriptGrammarParser.RULE_program);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 42;
			this.declarations(0);
			this.state = 43;
			this.match(ScriptGrammarParser.EOF);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public declarations(): DeclarationsContext;
	public declarations(_p: number): DeclarationsContext;
	// @RuleVersion(0)
	public declarations(_p?: number): DeclarationsContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: DeclarationsContext = new DeclarationsContext(this, this._ctx, _parentState);
		let _prevctx: DeclarationsContext = localctx;
		let _startState: number = 2;
		this.enterRecursionRule(localctx, 2, ScriptGrammarParser.RULE_declarations, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 51;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 1:
				{
				this.state = 46;
				this.classDeclaration();
				}
				break;
			case 10:
				{
				this.state = 47;
				this.functionDeclaration();
				}
				break;
			case 55:
				{
				this.state = 48;
				this.variableDeclaration();
				this.state = 49;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 57;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 1, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new DeclarationsContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_declarations);
					this.state = 53;
					if (!(this.precpred(this._ctx, 4))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 4)");
					}
					this.state = 54;
					this.declarations(5);
					}
					}
				}
				this.state = 59;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 1, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}
	// @RuleVersion(0)
	public classDeclaration(): ClassDeclarationContext {
		let localctx: ClassDeclarationContext = new ClassDeclarationContext(this, this._ctx, this.state);
		this.enterRule(localctx, 4, ScriptGrammarParser.RULE_classDeclaration);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 60;
			this.match(ScriptGrammarParser.T__0);
			this.state = 61;
			this.match(ScriptGrammarParser.ID);
			this.state = 65;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 2:
				{
				this.state = 62;
				this.match(ScriptGrammarParser.T__1);
				this.state = 63;
				this.match(ScriptGrammarParser.ID);
				}
				break;
			case 3:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 67;
			this.match(ScriptGrammarParser.T__2);
			this.state = 70;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 5:
			case 6:
			case 7:
			case 8:
			case 10:
			case 55:
				{
				this.state = 68;
				this.members(0);
				}
				break;
			case 4:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 72;
			this.match(ScriptGrammarParser.T__3);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public members(): MembersContext;
	public members(_p: number): MembersContext;
	// @RuleVersion(0)
	public members(_p?: number): MembersContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: MembersContext = new MembersContext(this, this._ctx, _parentState);
		let _prevctx: MembersContext = localctx;
		let _startState: number = 6;
		this.enterRecursionRule(localctx, 6, ScriptGrammarParser.RULE_members, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 75;
			this.member();
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 81;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 4, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new MembersContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_members);
					this.state = 77;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 78;
					this.members(3);
					}
					}
				}
				this.state = 83;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 4, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}
	// @RuleVersion(0)
	public member(): MemberContext {
		let localctx: MemberContext = new MemberContext(this, this._ctx, this.state);
		this.enterRule(localctx, 8, ScriptGrammarParser.RULE_member);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 88;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 5:
				{
				this.state = 84;
				this.match(ScriptGrammarParser.T__4);
				}
				break;
			case 6:
				{
				this.state = 85;
				this.match(ScriptGrammarParser.T__5);
				}
				break;
			case 7:
				{
				this.state = 86;
				this.match(ScriptGrammarParser.T__6);
				}
				break;
			case 8:
			case 10:
			case 55:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 92;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 8:
				{
				this.state = 90;
				this.match(ScriptGrammarParser.T__7);
				}
				break;
			case 10:
			case 55:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 98;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 10:
				{
				this.state = 94;
				this.functionDeclaration();
				}
				break;
			case 55:
				{
				this.state = 95;
				this.variableDeclaration();
				this.state = 96;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public variableDeclaration(): VariableDeclarationContext {
		let localctx: VariableDeclarationContext = new VariableDeclarationContext(this, this._ctx, this.state);
		this.enterRule(localctx, 10, ScriptGrammarParser.RULE_variableDeclaration);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 100;
			this.match(ScriptGrammarParser.ID);
			this.state = 101;
			this.match(ScriptGrammarParser.T__8);
			this.state = 102;
			this.expression(0);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public functionDeclaration(): FunctionDeclarationContext {
		let localctx: FunctionDeclarationContext = new FunctionDeclarationContext(this, this._ctx, this.state);
		this.enterRule(localctx, 12, ScriptGrammarParser.RULE_functionDeclaration);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 104;
			this.match(ScriptGrammarParser.T__9);
			this.state = 105;
			this.match(ScriptGrammarParser.ID);
			this.state = 113;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 11:
				{
				this.state = 106;
				this.match(ScriptGrammarParser.T__10);
				this.state = 109;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 55:
					{
					this.state = 107;
					this.params(0);
					}
					break;
				case 12:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 111;
				this.match(ScriptGrammarParser.T__11);
				}
				break;
			case 3:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 115;
			this.blockStatement();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public params(): ParamsContext;
	public params(_p: number): ParamsContext;
	// @RuleVersion(0)
	public params(_p?: number): ParamsContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: ParamsContext = new ParamsContext(this, this._ctx, _parentState);
		let _prevctx: ParamsContext = localctx;
		let _startState: number = 14;
		this.enterRecursionRule(localctx, 14, ScriptGrammarParser.RULE_params, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 118;
			this.match(ScriptGrammarParser.ID);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 125;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 10, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new ParamsContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_params);
					this.state = 120;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 121;
					this.match(ScriptGrammarParser.T__12);
					this.state = 122;
					this.params(3);
					}
					}
				}
				this.state = 127;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 10, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}

	public statements(): StatementsContext;
	public statements(_p: number): StatementsContext;
	// @RuleVersion(0)
	public statements(_p?: number): StatementsContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: StatementsContext = new StatementsContext(this, this._ctx, _parentState);
		let _prevctx: StatementsContext = localctx;
		let _startState: number = 16;
		this.enterRecursionRule(localctx, 16, ScriptGrammarParser.RULE_statements, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 146;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 11:
			case 22:
			case 23:
			case 24:
			case 25:
			case 36:
			case 42:
			case 43:
			case 44:
			case 45:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
				{
				this.state = 129;
				this.expression(0);
				this.state = 130;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			case 15:
				{
				this.state = 132;
				this.ifStatement();
				}
				break;
			case 16:
				{
				this.state = 133;
				this.forStatement();
				}
				break;
			case 18:
				{
				this.state = 134;
				this.whileStatement();
				}
				break;
			case 19:
				{
				this.state = 135;
				this.returnStatement();
				this.state = 136;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			case 20:
				{
				this.state = 138;
				this.continueStatement();
				this.state = 139;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			case 21:
				{
				this.state = 141;
				this.breakStatement();
				this.state = 142;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			case 3:
				{
				this.state = 144;
				this.blockStatement();
				}
				break;
			case 50:
				{
				this.state = 145;
				this.match(ScriptGrammarParser.SEMI);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 152;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 12, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new StatementsContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_statements);
					this.state = 148;
					if (!(this.precpred(this._ctx, 10))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 10)");
					}
					this.state = 149;
					this.statements(11);
					}
					}
				}
				this.state = 154;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 12, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}
	// @RuleVersion(0)
	public blockStatement(): BlockStatementContext {
		let localctx: BlockStatementContext = new BlockStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 18, ScriptGrammarParser.RULE_blockStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 155;
			this.match(ScriptGrammarParser.T__2);
			this.state = 158;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 3:
			case 11:
			case 15:
			case 16:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 36:
			case 42:
			case 43:
			case 44:
			case 45:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
				{
				this.state = 156;
				this.statements(0);
				}
				break;
			case 4:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this.state = 160;
			this.match(ScriptGrammarParser.T__3);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public ifStatement(): IfStatementContext {
		let localctx: IfStatementContext = new IfStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 20, ScriptGrammarParser.RULE_ifStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 162;
			this.multiIfStatement(0);
			this.state = 163;
			this.elseStatement();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public multiIfStatement(): MultiIfStatementContext;
	public multiIfStatement(_p: number): MultiIfStatementContext;
	// @RuleVersion(0)
	public multiIfStatement(_p?: number): MultiIfStatementContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: MultiIfStatementContext = new MultiIfStatementContext(this, this._ctx, _parentState);
		let _prevctx: MultiIfStatementContext = localctx;
		let _startState: number = 22;
		this.enterRecursionRule(localctx, 22, ScriptGrammarParser.RULE_multiIfStatement, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 166;
			this.match(ScriptGrammarParser.T__14);
			this.state = 167;
			this.match(ScriptGrammarParser.T__10);
			this.state = 168;
			this.expression(0);
			this.state = 169;
			this.match(ScriptGrammarParser.T__11);
			this.state = 170;
			this.blockStatement();
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 177;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 14, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new MultiIfStatementContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_multiIfStatement);
					this.state = 172;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 173;
					this.match(ScriptGrammarParser.T__13);
					this.state = 174;
					this.multiIfStatement(3);
					}
					}
				}
				this.state = 179;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 14, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}
	// @RuleVersion(0)
	public elseStatement(): ElseStatementContext {
		let localctx: ElseStatementContext = new ElseStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 24, ScriptGrammarParser.RULE_elseStatement);
		try {
			this.state = 183;
			this._errHandler.sync(this);
			switch ( this._interp.adaptivePredict(this._input, 15, this._ctx) ) {
			case 1:
				this.enterOuterAlt(localctx, 1);
				{
				this.state = 180;
				this.match(ScriptGrammarParser.T__13);
				this.state = 181;
				this.blockStatement();
				}
				break;
			case 2:
				this.enterOuterAlt(localctx, 2);
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public forStatement(): ForStatementContext {
		let localctx: ForStatementContext = new ForStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 26, ScriptGrammarParser.RULE_forStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 185;
			this.match(ScriptGrammarParser.T__15);
			this.state = 186;
			this.match(ScriptGrammarParser.T__10);
			this.state = 205;
			this._errHandler.sync(this);
			switch ( this._interp.adaptivePredict(this._input, 19, this._ctx) ) {
			case 1:
				{
				this.state = 189;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 11:
				case 22:
				case 23:
				case 24:
				case 25:
				case 36:
				case 42:
				case 43:
				case 44:
				case 45:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
					{
					this.state = 187;
					this.expression(0);
					}
					break;
				case 50:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 191;
				this.match(ScriptGrammarParser.SEMI);
				this.state = 194;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 11:
				case 22:
				case 23:
				case 24:
				case 25:
				case 36:
				case 42:
				case 43:
				case 44:
				case 45:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
					{
					this.state = 192;
					this.expression(0);
					}
					break;
				case 50:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 196;
				this.match(ScriptGrammarParser.SEMI);
				this.state = 199;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 11:
				case 22:
				case 23:
				case 24:
				case 25:
				case 36:
				case 42:
				case 43:
				case 44:
				case 45:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
					{
					this.state = 197;
					this.expression(0);
					}
					break;
				case 12:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			case 2:
				{
				this.state = 201;
				this.expression(0);
				this.state = 202;
				this.match(ScriptGrammarParser.T__16);
				this.state = 203;
				this.expression(0);
				}
				break;
			}
			this.state = 207;
			this.match(ScriptGrammarParser.T__11);
			this.state = 208;
			this.blockStatement();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public whileStatement(): WhileStatementContext {
		let localctx: WhileStatementContext = new WhileStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 28, ScriptGrammarParser.RULE_whileStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 210;
			this.match(ScriptGrammarParser.T__17);
			this.state = 211;
			this.match(ScriptGrammarParser.T__10);
			this.state = 212;
			this.expression(0);
			this.state = 213;
			this.match(ScriptGrammarParser.T__11);
			this.state = 214;
			this.blockStatement();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public returnStatement(): ReturnStatementContext {
		let localctx: ReturnStatementContext = new ReturnStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 30, ScriptGrammarParser.RULE_returnStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 216;
			this.match(ScriptGrammarParser.T__18);
			this.state = 219;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 11:
			case 22:
			case 23:
			case 24:
			case 25:
			case 36:
			case 42:
			case 43:
			case 44:
			case 45:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
				{
				this.state = 217;
				this.expression(0);
				}
				break;
			case 50:
				// tslint:disable-next-line:no-empty
				{
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public continueStatement(): ContinueStatementContext {
		let localctx: ContinueStatementContext = new ContinueStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 32, ScriptGrammarParser.RULE_continueStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 221;
			this.match(ScriptGrammarParser.T__19);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}
	// @RuleVersion(0)
	public breakStatement(): BreakStatementContext {
		let localctx: BreakStatementContext = new BreakStatementContext(this, this._ctx, this.state);
		this.enterRule(localctx, 34, ScriptGrammarParser.RULE_breakStatement);
		try {
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 223;
			this.match(ScriptGrammarParser.T__20);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return localctx;
	}

	public expression(): ExpressionContext;
	public expression(_p: number): ExpressionContext;
	// @RuleVersion(0)
	public expression(_p?: number): ExpressionContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: ExpressionContext = new ExpressionContext(this, this._ctx, _parentState);
		let _prevctx: ExpressionContext = localctx;
		let _startState: number = 36;
		this.enterRecursionRule(localctx, 36, ScriptGrammarParser.RULE_expression, _p);
		let _la: number;
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 244;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 22:
			case 23:
			case 24:
			case 25:
				{
				this.state = 226;
				_la = this._input.LA(1);
				if(!((((_la) & ~0x1F) === 0 && ((1 << _la) & 62914560) !== 0))) {
				this._errHandler.recoverInline(this);
				}
				else {
					this._errHandler.reportMatch(this);
				    this.consume();
				}
				this.state = 227;
				this.expression(14);
				}
				break;
			case 36:
				{
				this.state = 228;
				this.match(ScriptGrammarParser.T__35);
				this.state = 229;
				this.expression(8);
				}
				break;
			case 11:
			case 42:
			case 55:
				{
				this.state = 237;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 42:
					{
					this.state = 230;
					this.match(ScriptGrammarParser.T__41);
					this.state = 231;
					this.match(ScriptGrammarParser.ID);
					}
					break;
				case 55:
					{
					this.state = 232;
					this.match(ScriptGrammarParser.ID);
					}
					break;
				case 11:
					{
					this.state = 233;
					this.match(ScriptGrammarParser.T__10);
					this.state = 234;
					this.expression(0);
					this.state = 235;
					this.match(ScriptGrammarParser.T__11);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 241;
				this._errHandler.sync(this);
				switch ( this._interp.adaptivePredict(this._input, 22, this._ctx) ) {
				case 1:
					{
					this.state = 239;
					this.accessExpression(0);
					}
					break;
				case 2:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				}
				}
				break;
			case 43:
			case 44:
			case 45:
			case 51:
			case 52:
			case 53:
			case 54:
			case 56:
				{
				this.state = 243;
				_la = this._input.LA(1);
				if(!(((((_la - 43)) & ~0x1F) === 0 && ((1 << (_la - 43)) & 12039) !== 0))) {
				this._errHandler.recoverInline(this);
				}
				else {
					this._errHandler.reportMatch(this);
				    this.consume();
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 281;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 25, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					this.state = 279;
					this._errHandler.sync(this);
					switch ( this._interp.adaptivePredict(this._input, 24, this._ctx) ) {
					case 1:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 246;
						if (!(this.precpred(this._ctx, 13))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 13)");
						}
						this.state = 247;
						_la = this._input.LA(1);
						if(!((((_la) & ~0x1F) === 0 && ((1 << _la) & 469762048) !== 0))) {
						this._errHandler.recoverInline(this);
						}
						else {
							this._errHandler.reportMatch(this);
						    this.consume();
						}
						this.state = 248;
						this.expression(14);
						}
						break;
					case 2:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 249;
						if (!(this.precpred(this._ctx, 12))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 12)");
						}
						this.state = 250;
						_la = this._input.LA(1);
						if(!(_la===24 || _la===25)) {
						this._errHandler.recoverInline(this);
						}
						else {
							this._errHandler.reportMatch(this);
						    this.consume();
						}
						this.state = 251;
						this.expression(13);
						}
						break;
					case 3:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 252;
						if (!(this.precpred(this._ctx, 11))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 11)");
						}
						this.state = 253;
						_la = this._input.LA(1);
						if(!(((((_la - 29)) & ~0x1F) === 0 && ((1 << (_la - 29)) & 15) !== 0))) {
						this._errHandler.recoverInline(this);
						}
						else {
							this._errHandler.reportMatch(this);
						    this.consume();
						}
						this.state = 254;
						this.expression(12);
						}
						break;
					case 4:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 255;
						if (!(this.precpred(this._ctx, 10))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 10)");
						}
						this.state = 256;
						_la = this._input.LA(1);
						if(!(_la===33 || _la===34)) {
						this._errHandler.recoverInline(this);
						}
						else {
							this._errHandler.reportMatch(this);
						    this.consume();
						}
						this.state = 257;
						this.expression(11);
						}
						break;
					case 5:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 258;
						if (!(this.precpred(this._ctx, 9))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 9)");
						}
						this.state = 259;
						this.match(ScriptGrammarParser.T__34);
						this.state = 260;
						this.expression(10);
						}
						break;
					case 6:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 261;
						if (!(this.precpred(this._ctx, 7))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 7)");
						}
						this.state = 262;
						this.match(ScriptGrammarParser.T__36);
						this.state = 263;
						this.expression(8);
						}
						break;
					case 7:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 264;
						if (!(this.precpred(this._ctx, 6))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 6)");
						}
						this.state = 265;
						this.match(ScriptGrammarParser.T__37);
						this.state = 266;
						this.expression(7);
						}
						break;
					case 8:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 267;
						if (!(this.precpred(this._ctx, 5))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 5)");
						}
						this.state = 268;
						this.match(ScriptGrammarParser.T__38);
						this.state = 269;
						this.expression(6);
						}
						break;
					case 9:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 270;
						if (!(this.precpred(this._ctx, 4))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 4)");
						}
						this.state = 271;
						this.match(ScriptGrammarParser.T__39);
						this.state = 272;
						this.expression(0);
						this.state = 273;
						this.match(ScriptGrammarParser.T__40);
						this.state = 274;
						this.expression(4);
						}
						break;
					case 10:
						{
						localctx = new ExpressionContext(this, _parentctx, _parentState);
						this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expression);
						this.state = 276;
						if (!(this.precpred(this._ctx, 1))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 1)");
						}
						this.state = 277;
						this.match(ScriptGrammarParser.T__8);
						this.state = 278;
						this.expression(1);
						}
						break;
					}
					}
				}
				this.state = 283;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 25, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}

	public accessExpression(): AccessExpressionContext;
	public accessExpression(_p: number): AccessExpressionContext;
	// @RuleVersion(0)
	public accessExpression(_p?: number): AccessExpressionContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: AccessExpressionContext = new AccessExpressionContext(this, this._ctx, _parentState);
		let _prevctx: AccessExpressionContext = localctx;
		let _startState: number = 38;
		this.enterRecursionRule(localctx, 38, ScriptGrammarParser.RULE_accessExpression, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			this.state = 297;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case 46:
				{
				this.state = 285;
				this.match(ScriptGrammarParser.T__45);
				this.state = 286;
				this.expression(0);
				this.state = 287;
				this.match(ScriptGrammarParser.T__46);
				}
				break;
			case 11:
				{
				this.state = 289;
				this.match(ScriptGrammarParser.T__10);
				this.state = 292;
				this._errHandler.sync(this);
				switch (this._input.LA(1)) {
				case 11:
				case 22:
				case 23:
				case 24:
				case 25:
				case 36:
				case 42:
				case 43:
				case 44:
				case 45:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
					{
					this.state = 290;
					this.arguments(0);
					}
					break;
				case 12:
					// tslint:disable-next-line:no-empty
					{
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				this.state = 294;
				this.match(ScriptGrammarParser.T__11);
				}
				break;
			case 48:
				{
				this.state = 295;
				this.match(ScriptGrammarParser.T__47);
				this.state = 296;
				this.match(ScriptGrammarParser.ID);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 303;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 28, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new AccessExpressionContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_accessExpression);
					this.state = 299;
					if (!(this.precpred(this._ctx, 4))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 4)");
					}
					this.state = 300;
					this.accessExpression(5);
					}
					}
				}
				this.state = 305;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 28, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}

	public arguments(): ArgumentsContext;
	public arguments(_p: number): ArgumentsContext;
	// @RuleVersion(0)
	public arguments(_p?: number): ArgumentsContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let localctx: ArgumentsContext = new ArgumentsContext(this, this._ctx, _parentState);
		let _prevctx: ArgumentsContext = localctx;
		let _startState: number = 40;
		this.enterRecursionRule(localctx, 40, ScriptGrammarParser.RULE_arguments, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(localctx, 1);
			{
			{
			this.state = 307;
			this.expression(0);
			}
			this._ctx.stop = this._input.LT(-1);
			this.state = 314;
			this._errHandler.sync(this);
			_alt = this._interp.adaptivePredict(this._input, 29, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = localctx;
					{
					{
					localctx = new ArgumentsContext(this, _parentctx, _parentState);
					this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_arguments);
					this.state = 309;
					if (!(this.precpred(this._ctx, 2))) {
						throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
					}
					this.state = 310;
					this.match(ScriptGrammarParser.T__12);
					this.state = 311;
					this.arguments(3);
					}
					}
				}
				this.state = 316;
				this._errHandler.sync(this);
				_alt = this._interp.adaptivePredict(this._input, 29, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return localctx;
	}

	public sempred(localctx: RuleContext, ruleIndex: number, predIndex: number): boolean {
		switch (ruleIndex) {
		case 1:
			return this.declarations_sempred(localctx as DeclarationsContext, predIndex);
		case 3:
			return this.members_sempred(localctx as MembersContext, predIndex);
		case 7:
			return this.params_sempred(localctx as ParamsContext, predIndex);
		case 8:
			return this.statements_sempred(localctx as StatementsContext, predIndex);
		case 11:
			return this.multiIfStatement_sempred(localctx as MultiIfStatementContext, predIndex);
		case 18:
			return this.expression_sempred(localctx as ExpressionContext, predIndex);
		case 19:
			return this.accessExpression_sempred(localctx as AccessExpressionContext, predIndex);
		case 20:
			return this.arguments_sempred(localctx as ArgumentsContext, predIndex);
		}
		return true;
	}
	private declarations_sempred(localctx: DeclarationsContext, predIndex: number): boolean {
		switch (predIndex) {
		case 0:
			return this.precpred(this._ctx, 4);
		}
		return true;
	}
	private members_sempred(localctx: MembersContext, predIndex: number): boolean {
		switch (predIndex) {
		case 1:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}
	private params_sempred(localctx: ParamsContext, predIndex: number): boolean {
		switch (predIndex) {
		case 2:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}
	private statements_sempred(localctx: StatementsContext, predIndex: number): boolean {
		switch (predIndex) {
		case 3:
			return this.precpred(this._ctx, 10);
		}
		return true;
	}
	private multiIfStatement_sempred(localctx: MultiIfStatementContext, predIndex: number): boolean {
		switch (predIndex) {
		case 4:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}
	private expression_sempred(localctx: ExpressionContext, predIndex: number): boolean {
		switch (predIndex) {
		case 5:
			return this.precpred(this._ctx, 13);
		case 6:
			return this.precpred(this._ctx, 12);
		case 7:
			return this.precpred(this._ctx, 11);
		case 8:
			return this.precpred(this._ctx, 10);
		case 9:
			return this.precpred(this._ctx, 9);
		case 10:
			return this.precpred(this._ctx, 7);
		case 11:
			return this.precpred(this._ctx, 6);
		case 12:
			return this.precpred(this._ctx, 5);
		case 13:
			return this.precpred(this._ctx, 4);
		case 14:
			return this.precpred(this._ctx, 1);
		}
		return true;
	}
	private accessExpression_sempred(localctx: AccessExpressionContext, predIndex: number): boolean {
		switch (predIndex) {
		case 15:
			return this.precpred(this._ctx, 4);
		}
		return true;
	}
	private arguments_sempred(localctx: ArgumentsContext, predIndex: number): boolean {
		switch (predIndex) {
		case 16:
			return this.precpred(this._ctx, 2);
		}
		return true;
	}

	public static readonly _serializedATN: number[] = [4,1,58,318,2,0,7,0,2,
	1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,
	10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,
	7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,
	3,1,52,8,1,1,1,1,1,5,1,56,8,1,10,1,12,1,59,9,1,1,2,1,2,1,2,1,2,1,2,3,2,
	66,8,2,1,2,1,2,1,2,3,2,71,8,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,80,8,3,10,
	3,12,3,83,9,3,1,4,1,4,1,4,1,4,3,4,89,8,4,1,4,1,4,3,4,93,8,4,1,4,1,4,1,4,
	1,4,3,4,99,8,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,3,6,110,8,6,1,6,1,6,
	3,6,114,8,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,5,7,124,8,7,10,7,12,7,127,9,
	7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
	8,3,8,147,8,8,1,8,1,8,5,8,151,8,8,10,8,12,8,154,9,8,1,9,1,9,1,9,3,9,159,
	8,9,1,9,1,9,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
	1,11,5,11,176,8,11,10,11,12,11,179,9,11,1,12,1,12,1,12,3,12,184,8,12,1,
	13,1,13,1,13,1,13,3,13,190,8,13,1,13,1,13,1,13,3,13,195,8,13,1,13,1,13,
	1,13,3,13,200,8,13,1,13,1,13,1,13,1,13,3,13,206,8,13,1,13,1,13,1,13,1,14,
	1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,3,15,220,8,15,1,16,1,16,1,17,1,
	17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,238,
	8,18,1,18,1,18,3,18,242,8,18,1,18,3,18,245,8,18,1,18,1,18,1,18,1,18,1,18,
	1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,
	18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,5,18,
	280,8,18,10,18,12,18,283,9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,
	19,293,8,19,1,19,1,19,1,19,3,19,298,8,19,1,19,1,19,5,19,302,8,19,10,19,
	12,19,305,9,19,1,20,1,20,1,20,1,20,1,20,1,20,5,20,313,8,20,10,20,12,20,
	316,9,20,1,20,0,8,2,6,14,16,22,36,38,40,21,0,2,4,6,8,10,12,14,16,18,20,
	22,24,26,28,30,32,34,36,38,40,0,6,1,0,22,25,3,0,43,45,51,54,56,56,1,0,26,
	28,1,0,24,25,1,0,29,32,1,0,33,34,348,0,42,1,0,0,0,2,51,1,0,0,0,4,60,1,0,
	0,0,6,74,1,0,0,0,8,88,1,0,0,0,10,100,1,0,0,0,12,104,1,0,0,0,14,117,1,0,
	0,0,16,146,1,0,0,0,18,155,1,0,0,0,20,162,1,0,0,0,22,165,1,0,0,0,24,183,
	1,0,0,0,26,185,1,0,0,0,28,210,1,0,0,0,30,216,1,0,0,0,32,221,1,0,0,0,34,
	223,1,0,0,0,36,244,1,0,0,0,38,297,1,0,0,0,40,306,1,0,0,0,42,43,3,2,1,0,
	43,44,5,0,0,1,44,1,1,0,0,0,45,46,6,1,-1,0,46,52,3,4,2,0,47,52,3,12,6,0,
	48,49,3,10,5,0,49,50,5,50,0,0,50,52,1,0,0,0,51,45,1,0,0,0,51,47,1,0,0,0,
	51,48,1,0,0,0,52,57,1,0,0,0,53,54,10,4,0,0,54,56,3,2,1,5,55,53,1,0,0,0,
	56,59,1,0,0,0,57,55,1,0,0,0,57,58,1,0,0,0,58,3,1,0,0,0,59,57,1,0,0,0,60,
	61,5,1,0,0,61,65,5,55,0,0,62,63,5,2,0,0,63,66,5,55,0,0,64,66,1,0,0,0,65,
	62,1,0,0,0,65,64,1,0,0,0,66,67,1,0,0,0,67,70,5,3,0,0,68,71,3,6,3,0,69,71,
	1,0,0,0,70,68,1,0,0,0,70,69,1,0,0,0,71,72,1,0,0,0,72,73,5,4,0,0,73,5,1,
	0,0,0,74,75,6,3,-1,0,75,76,3,8,4,0,76,81,1,0,0,0,77,78,10,2,0,0,78,80,3,
	6,3,3,79,77,1,0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,7,1,0,
	0,0,83,81,1,0,0,0,84,89,5,5,0,0,85,89,5,6,0,0,86,89,5,7,0,0,87,89,1,0,0,
	0,88,84,1,0,0,0,88,85,1,0,0,0,88,86,1,0,0,0,88,87,1,0,0,0,89,92,1,0,0,0,
	90,93,5,8,0,0,91,93,1,0,0,0,92,90,1,0,0,0,92,91,1,0,0,0,93,98,1,0,0,0,94,
	99,3,12,6,0,95,96,3,10,5,0,96,97,5,50,0,0,97,99,1,0,0,0,98,94,1,0,0,0,98,
	95,1,0,0,0,99,9,1,0,0,0,100,101,5,55,0,0,101,102,5,9,0,0,102,103,3,36,18,
	0,103,11,1,0,0,0,104,105,5,10,0,0,105,113,5,55,0,0,106,109,5,11,0,0,107,
	110,3,14,7,0,108,110,1,0,0,0,109,107,1,0,0,0,109,108,1,0,0,0,110,111,1,
	0,0,0,111,114,5,12,0,0,112,114,1,0,0,0,113,106,1,0,0,0,113,112,1,0,0,0,
	114,115,1,0,0,0,115,116,3,18,9,0,116,13,1,0,0,0,117,118,6,7,-1,0,118,119,
	5,55,0,0,119,125,1,0,0,0,120,121,10,2,0,0,121,122,5,13,0,0,122,124,3,14,
	7,3,123,120,1,0,0,0,124,127,1,0,0,0,125,123,1,0,0,0,125,126,1,0,0,0,126,
	15,1,0,0,0,127,125,1,0,0,0,128,129,6,8,-1,0,129,130,3,36,18,0,130,131,5,
	50,0,0,131,147,1,0,0,0,132,147,3,20,10,0,133,147,3,26,13,0,134,147,3,28,
	14,0,135,136,3,30,15,0,136,137,5,50,0,0,137,147,1,0,0,0,138,139,3,32,16,
	0,139,140,5,50,0,0,140,147,1,0,0,0,141,142,3,34,17,0,142,143,5,50,0,0,143,
	147,1,0,0,0,144,147,3,18,9,0,145,147,5,50,0,0,146,128,1,0,0,0,146,132,1,
	0,0,0,146,133,1,0,0,0,146,134,1,0,0,0,146,135,1,0,0,0,146,138,1,0,0,0,146,
	141,1,0,0,0,146,144,1,0,0,0,146,145,1,0,0,0,147,152,1,0,0,0,148,149,10,
	10,0,0,149,151,3,16,8,11,150,148,1,0,0,0,151,154,1,0,0,0,152,150,1,0,0,
	0,152,153,1,0,0,0,153,17,1,0,0,0,154,152,1,0,0,0,155,158,5,3,0,0,156,159,
	3,16,8,0,157,159,1,0,0,0,158,156,1,0,0,0,158,157,1,0,0,0,159,160,1,0,0,
	0,160,161,5,4,0,0,161,19,1,0,0,0,162,163,3,22,11,0,163,164,3,24,12,0,164,
	21,1,0,0,0,165,166,6,11,-1,0,166,167,5,15,0,0,167,168,5,11,0,0,168,169,
	3,36,18,0,169,170,5,12,0,0,170,171,3,18,9,0,171,177,1,0,0,0,172,173,10,
	2,0,0,173,174,5,14,0,0,174,176,3,22,11,3,175,172,1,0,0,0,176,179,1,0,0,
	0,177,175,1,0,0,0,177,178,1,0,0,0,178,23,1,0,0,0,179,177,1,0,0,0,180,181,
	5,14,0,0,181,184,3,18,9,0,182,184,1,0,0,0,183,180,1,0,0,0,183,182,1,0,0,
	0,184,25,1,0,0,0,185,186,5,16,0,0,186,205,5,11,0,0,187,190,3,36,18,0,188,
	190,1,0,0,0,189,187,1,0,0,0,189,188,1,0,0,0,190,191,1,0,0,0,191,194,5,50,
	0,0,192,195,3,36,18,0,193,195,1,0,0,0,194,192,1,0,0,0,194,193,1,0,0,0,195,
	196,1,0,0,0,196,199,5,50,0,0,197,200,3,36,18,0,198,200,1,0,0,0,199,197,
	1,0,0,0,199,198,1,0,0,0,200,206,1,0,0,0,201,202,3,36,18,0,202,203,5,17,
	0,0,203,204,3,36,18,0,204,206,1,0,0,0,205,189,1,0,0,0,205,201,1,0,0,0,206,
	207,1,0,0,0,207,208,5,12,0,0,208,209,3,18,9,0,209,27,1,0,0,0,210,211,5,
	18,0,0,211,212,5,11,0,0,212,213,3,36,18,0,213,214,5,12,0,0,214,215,3,18,
	9,0,215,29,1,0,0,0,216,219,5,19,0,0,217,220,3,36,18,0,218,220,1,0,0,0,219,
	217,1,0,0,0,219,218,1,0,0,0,220,31,1,0,0,0,221,222,5,20,0,0,222,33,1,0,
	0,0,223,224,5,21,0,0,224,35,1,0,0,0,225,226,6,18,-1,0,226,227,7,0,0,0,227,
	245,3,36,18,14,228,229,5,36,0,0,229,245,3,36,18,8,230,231,5,42,0,0,231,
	238,5,55,0,0,232,238,5,55,0,0,233,234,5,11,0,0,234,235,3,36,18,0,235,236,
	5,12,0,0,236,238,1,0,0,0,237,230,1,0,0,0,237,232,1,0,0,0,237,233,1,0,0,
	0,238,241,1,0,0,0,239,242,3,38,19,0,240,242,1,0,0,0,241,239,1,0,0,0,241,
	240,1,0,0,0,242,245,1,0,0,0,243,245,7,1,0,0,244,225,1,0,0,0,244,228,1,0,
	0,0,244,237,1,0,0,0,244,243,1,0,0,0,245,281,1,0,0,0,246,247,10,13,0,0,247,
	248,7,2,0,0,248,280,3,36,18,14,249,250,10,12,0,0,250,251,7,3,0,0,251,280,
	3,36,18,13,252,253,10,11,0,0,253,254,7,4,0,0,254,280,3,36,18,12,255,256,
	10,10,0,0,256,257,7,5,0,0,257,280,3,36,18,11,258,259,10,9,0,0,259,260,5,
	35,0,0,260,280,3,36,18,10,261,262,10,7,0,0,262,263,5,37,0,0,263,280,3,36,
	18,8,264,265,10,6,0,0,265,266,5,38,0,0,266,280,3,36,18,7,267,268,10,5,0,
	0,268,269,5,39,0,0,269,280,3,36,18,6,270,271,10,4,0,0,271,272,5,40,0,0,
	272,273,3,36,18,0,273,274,5,41,0,0,274,275,3,36,18,4,275,280,1,0,0,0,276,
	277,10,1,0,0,277,278,5,9,0,0,278,280,3,36,18,1,279,246,1,0,0,0,279,249,
	1,0,0,0,279,252,1,0,0,0,279,255,1,0,0,0,279,258,1,0,0,0,279,261,1,0,0,0,
	279,264,1,0,0,0,279,267,1,0,0,0,279,270,1,0,0,0,279,276,1,0,0,0,280,283,
	1,0,0,0,281,279,1,0,0,0,281,282,1,0,0,0,282,37,1,0,0,0,283,281,1,0,0,0,
	284,285,6,19,-1,0,285,286,5,46,0,0,286,287,3,36,18,0,287,288,5,47,0,0,288,
	298,1,0,0,0,289,292,5,11,0,0,290,293,3,40,20,0,291,293,1,0,0,0,292,290,
	1,0,0,0,292,291,1,0,0,0,293,294,1,0,0,0,294,298,5,12,0,0,295,296,5,48,0,
	0,296,298,5,55,0,0,297,284,1,0,0,0,297,289,1,0,0,0,297,295,1,0,0,0,298,
	303,1,0,0,0,299,300,10,4,0,0,300,302,3,38,19,5,301,299,1,0,0,0,302,305,
	1,0,0,0,303,301,1,0,0,0,303,304,1,0,0,0,304,39,1,0,0,0,305,303,1,0,0,0,
	306,307,6,20,-1,0,307,308,3,36,18,0,308,314,1,0,0,0,309,310,10,2,0,0,310,
	311,5,13,0,0,311,313,3,40,20,3,312,309,1,0,0,0,313,316,1,0,0,0,314,312,
	1,0,0,0,314,315,1,0,0,0,315,41,1,0,0,0,316,314,1,0,0,0,30,51,57,65,70,81,
	88,92,98,109,113,125,146,152,158,177,183,189,194,199,205,219,237,241,244,
	279,281,292,297,303,314];

	private static __ATN: ATN;
	public static get _ATN(): ATN {
		if (!ScriptGrammarParser.__ATN) {
			ScriptGrammarParser.__ATN = new ATNDeserializer().deserialize(ScriptGrammarParser._serializedATN);
		}

		return ScriptGrammarParser.__ATN;
	}


	static DecisionsToDFA = ScriptGrammarParser._ATN.decisionToState.map( (ds: DecisionState, index: number) => new DFA(ds, index) );

}

export class ProgramContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public declarations(): DeclarationsContext {
		return this.getTypedRuleContext(DeclarationsContext, 0) as DeclarationsContext;
	}
	public EOF(): TerminalNode {
		return this.getToken(ScriptGrammarParser.EOF, 0);
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_program;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterProgram) {
	 		listener.enterProgram(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitProgram) {
	 		listener.exitProgram(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitProgram) {
			return visitor.visitProgram(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class DeclarationsContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public classDeclaration(): ClassDeclarationContext {
		return this.getTypedRuleContext(ClassDeclarationContext, 0) as ClassDeclarationContext;
	}
	public functionDeclaration(): FunctionDeclarationContext {
		return this.getTypedRuleContext(FunctionDeclarationContext, 0) as FunctionDeclarationContext;
	}
	public variableDeclaration(): VariableDeclarationContext {
		return this.getTypedRuleContext(VariableDeclarationContext, 0) as VariableDeclarationContext;
	}
	public SEMI(): TerminalNode {
		return this.getToken(ScriptGrammarParser.SEMI, 0);
	}
	public declarations_list(): DeclarationsContext[] {
		return this.getTypedRuleContexts(DeclarationsContext) as DeclarationsContext[];
	}
	public declarations(i: number): DeclarationsContext {
		return this.getTypedRuleContext(DeclarationsContext, i) as DeclarationsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_declarations;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterDeclarations) {
	 		listener.enterDeclarations(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitDeclarations) {
	 		listener.exitDeclarations(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitDeclarations) {
			return visitor.visitDeclarations(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ClassDeclarationContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public ID_list(): TerminalNode[] {
	    	return this.getTokens(ScriptGrammarParser.ID);
	}
	public ID(i: number): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, i);
	}
	public members(): MembersContext {
		return this.getTypedRuleContext(MembersContext, 0) as MembersContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_classDeclaration;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterClassDeclaration) {
	 		listener.enterClassDeclaration(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitClassDeclaration) {
	 		listener.exitClassDeclaration(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitClassDeclaration) {
			return visitor.visitClassDeclaration(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class MembersContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public member(): MemberContext {
		return this.getTypedRuleContext(MemberContext, 0) as MemberContext;
	}
	public members_list(): MembersContext[] {
		return this.getTypedRuleContexts(MembersContext) as MembersContext[];
	}
	public members(i: number): MembersContext {
		return this.getTypedRuleContext(MembersContext, i) as MembersContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_members;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterMembers) {
	 		listener.enterMembers(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitMembers) {
	 		listener.exitMembers(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitMembers) {
			return visitor.visitMembers(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class MemberContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public functionDeclaration(): FunctionDeclarationContext {
		return this.getTypedRuleContext(FunctionDeclarationContext, 0) as FunctionDeclarationContext;
	}
	public variableDeclaration(): VariableDeclarationContext {
		return this.getTypedRuleContext(VariableDeclarationContext, 0) as VariableDeclarationContext;
	}
	public SEMI(): TerminalNode {
		return this.getToken(ScriptGrammarParser.SEMI, 0);
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_member;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterMember) {
	 		listener.enterMember(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitMember) {
	 		listener.exitMember(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitMember) {
			return visitor.visitMember(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class VariableDeclarationContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public ID(): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, 0);
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_variableDeclaration;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterVariableDeclaration) {
	 		listener.enterVariableDeclaration(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitVariableDeclaration) {
	 		listener.exitVariableDeclaration(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitVariableDeclaration) {
			return visitor.visitVariableDeclaration(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class FunctionDeclarationContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public ID(): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, 0);
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
	public params(): ParamsContext {
		return this.getTypedRuleContext(ParamsContext, 0) as ParamsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_functionDeclaration;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterFunctionDeclaration) {
	 		listener.enterFunctionDeclaration(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitFunctionDeclaration) {
	 		listener.exitFunctionDeclaration(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitFunctionDeclaration) {
			return visitor.visitFunctionDeclaration(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ParamsContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public ID(): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, 0);
	}
	public params_list(): ParamsContext[] {
		return this.getTypedRuleContexts(ParamsContext) as ParamsContext[];
	}
	public params(i: number): ParamsContext {
		return this.getTypedRuleContext(ParamsContext, i) as ParamsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_params;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterParams) {
	 		listener.enterParams(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitParams) {
	 		listener.exitParams(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitParams) {
			return visitor.visitParams(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class StatementsContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public SEMI(): TerminalNode {
		return this.getToken(ScriptGrammarParser.SEMI, 0);
	}
	public ifStatement(): IfStatementContext {
		return this.getTypedRuleContext(IfStatementContext, 0) as IfStatementContext;
	}
	public forStatement(): ForStatementContext {
		return this.getTypedRuleContext(ForStatementContext, 0) as ForStatementContext;
	}
	public whileStatement(): WhileStatementContext {
		return this.getTypedRuleContext(WhileStatementContext, 0) as WhileStatementContext;
	}
	public returnStatement(): ReturnStatementContext {
		return this.getTypedRuleContext(ReturnStatementContext, 0) as ReturnStatementContext;
	}
	public continueStatement(): ContinueStatementContext {
		return this.getTypedRuleContext(ContinueStatementContext, 0) as ContinueStatementContext;
	}
	public breakStatement(): BreakStatementContext {
		return this.getTypedRuleContext(BreakStatementContext, 0) as BreakStatementContext;
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
	public statements_list(): StatementsContext[] {
		return this.getTypedRuleContexts(StatementsContext) as StatementsContext[];
	}
	public statements(i: number): StatementsContext {
		return this.getTypedRuleContext(StatementsContext, i) as StatementsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_statements;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterStatements) {
	 		listener.enterStatements(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitStatements) {
	 		listener.exitStatements(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitStatements) {
			return visitor.visitStatements(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class BlockStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public statements(): StatementsContext {
		return this.getTypedRuleContext(StatementsContext, 0) as StatementsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_blockStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterBlockStatement) {
	 		listener.enterBlockStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitBlockStatement) {
	 		listener.exitBlockStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitBlockStatement) {
			return visitor.visitBlockStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class IfStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public multiIfStatement(): MultiIfStatementContext {
		return this.getTypedRuleContext(MultiIfStatementContext, 0) as MultiIfStatementContext;
	}
	public elseStatement(): ElseStatementContext {
		return this.getTypedRuleContext(ElseStatementContext, 0) as ElseStatementContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_ifStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterIfStatement) {
	 		listener.enterIfStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitIfStatement) {
	 		listener.exitIfStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitIfStatement) {
			return visitor.visitIfStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class MultiIfStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
	public multiIfStatement_list(): MultiIfStatementContext[] {
		return this.getTypedRuleContexts(MultiIfStatementContext) as MultiIfStatementContext[];
	}
	public multiIfStatement(i: number): MultiIfStatementContext {
		return this.getTypedRuleContext(MultiIfStatementContext, i) as MultiIfStatementContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_multiIfStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterMultiIfStatement) {
	 		listener.enterMultiIfStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitMultiIfStatement) {
	 		listener.exitMultiIfStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitMultiIfStatement) {
			return visitor.visitMultiIfStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ElseStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_elseStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterElseStatement) {
	 		listener.enterElseStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitElseStatement) {
	 		listener.exitElseStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitElseStatement) {
			return visitor.visitElseStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ForStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
	public SEMI_list(): TerminalNode[] {
	    	return this.getTokens(ScriptGrammarParser.SEMI);
	}
	public SEMI(i: number): TerminalNode {
		return this.getToken(ScriptGrammarParser.SEMI, i);
	}
	public expression_list(): ExpressionContext[] {
		return this.getTypedRuleContexts(ExpressionContext) as ExpressionContext[];
	}
	public expression(i: number): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, i) as ExpressionContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_forStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterForStatement) {
	 		listener.enterForStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitForStatement) {
	 		listener.exitForStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitForStatement) {
			return visitor.visitForStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class WhileStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public blockStatement(): BlockStatementContext {
		return this.getTypedRuleContext(BlockStatementContext, 0) as BlockStatementContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_whileStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterWhileStatement) {
	 		listener.enterWhileStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitWhileStatement) {
	 		listener.exitWhileStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitWhileStatement) {
			return visitor.visitWhileStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ReturnStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_returnStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterReturnStatement) {
	 		listener.enterReturnStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitReturnStatement) {
	 		listener.exitReturnStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitReturnStatement) {
			return visitor.visitReturnStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ContinueStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_continueStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterContinueStatement) {
	 		listener.enterContinueStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitContinueStatement) {
	 		listener.exitContinueStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitContinueStatement) {
			return visitor.visitContinueStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class BreakStatementContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_breakStatement;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterBreakStatement) {
	 		listener.enterBreakStatement(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitBreakStatement) {
	 		listener.exitBreakStatement(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitBreakStatement) {
			return visitor.visitBreakStatement(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ExpressionContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression_list(): ExpressionContext[] {
		return this.getTypedRuleContexts(ExpressionContext) as ExpressionContext[];
	}
	public expression(i: number): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, i) as ExpressionContext;
	}
	public ID(): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, 0);
	}
	public accessExpression(): AccessExpressionContext {
		return this.getTypedRuleContext(AccessExpressionContext, 0) as AccessExpressionContext;
	}
	public NUMBER(): TerminalNode {
		return this.getToken(ScriptGrammarParser.NUMBER, 0);
	}
	public HEX(): TerminalNode {
		return this.getToken(ScriptGrammarParser.HEX, 0);
	}
	public OCT(): TerminalNode {
		return this.getToken(ScriptGrammarParser.OCT, 0);
	}
	public BIN(): TerminalNode {
		return this.getToken(ScriptGrammarParser.BIN, 0);
	}
	public STRING(): TerminalNode {
		return this.getToken(ScriptGrammarParser.STRING, 0);
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_expression;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterExpression) {
	 		listener.enterExpression(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitExpression) {
	 		listener.exitExpression(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitExpression) {
			return visitor.visitExpression(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class AccessExpressionContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public arguments(): ArgumentsContext {
		return this.getTypedRuleContext(ArgumentsContext, 0) as ArgumentsContext;
	}
	public ID(): TerminalNode {
		return this.getToken(ScriptGrammarParser.ID, 0);
	}
	public accessExpression_list(): AccessExpressionContext[] {
		return this.getTypedRuleContexts(AccessExpressionContext) as AccessExpressionContext[];
	}
	public accessExpression(i: number): AccessExpressionContext {
		return this.getTypedRuleContext(AccessExpressionContext, i) as AccessExpressionContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_accessExpression;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterAccessExpression) {
	 		listener.enterAccessExpression(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitAccessExpression) {
	 		listener.exitAccessExpression(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitAccessExpression) {
			return visitor.visitAccessExpression(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}


export class ArgumentsContext extends ParserRuleContext {
	constructor(parser?: ScriptGrammarParser, parent?: ParserRuleContext, invokingState?: number) {
		super(parent, invokingState);
    	this.parser = parser;
	}
	public expression(): ExpressionContext {
		return this.getTypedRuleContext(ExpressionContext, 0) as ExpressionContext;
	}
	public arguments_list(): ArgumentsContext[] {
		return this.getTypedRuleContexts(ArgumentsContext) as ArgumentsContext[];
	}
	public arguments(i: number): ArgumentsContext {
		return this.getTypedRuleContext(ArgumentsContext, i) as ArgumentsContext;
	}
    public get ruleIndex(): number {
    	return ScriptGrammarParser.RULE_arguments;
	}
	public enterRule(listener: ScriptGrammarListener): void {
	    if(listener.enterArguments) {
	 		listener.enterArguments(this);
		}
	}
	public exitRule(listener: ScriptGrammarListener): void {
	    if(listener.exitArguments) {
	 		listener.exitArguments(this);
		}
	}
	// @Override
	public accept<Result>(visitor: ScriptGrammarVisitor<Result>): Result {
		if (visitor.visitArguments) {
			return visitor.visitArguments(this);
		} else {
			return visitor.visitChildren(this);
		}
	}
}
