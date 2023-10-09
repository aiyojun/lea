// Generated from C:/Users/jun.dai/Documents/GitHub/lea/grammar/ScriptGrammar.g4 by ANTLR 4.13.1
// jshint ignore: start
import antlr4 from 'antlr4';
import ScriptGrammarListener from './ScriptGrammarListener.js';
import ScriptGrammarVisitor from './ScriptGrammarVisitor.js';

const serializedATN = [4,1,55,362,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,
4,2,5,7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,
2,13,7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,
20,7,20,2,21,7,21,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,54,8,1,1,1,1,1,
5,1,58,8,1,10,1,12,1,61,9,1,1,2,1,2,1,2,1,2,1,2,3,2,68,8,2,1,2,1,2,1,2,3,
2,73,8,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,82,8,3,10,3,12,3,85,9,3,1,4,1,4,
1,4,1,4,3,4,91,8,4,1,4,1,4,3,4,95,8,4,1,4,1,4,1,4,1,4,3,4,101,8,4,1,5,1,
5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,3,6,112,8,6,1,6,1,6,3,6,116,8,6,1,6,1,6,1,
6,3,6,121,8,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,5,7,131,8,7,10,7,12,7,134,
9,7,1,8,1,8,1,8,1,8,3,8,140,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
1,8,1,8,1,8,1,8,1,8,1,8,3,8,158,8,8,1,8,3,8,161,8,8,1,8,1,8,5,8,165,8,8,
10,8,12,8,168,9,8,1,9,1,9,1,9,3,9,173,8,9,1,9,1,9,3,9,177,8,9,1,10,1,10,
1,10,1,10,1,10,1,10,1,10,3,10,186,8,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,
5,11,195,8,11,10,11,12,11,198,9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
12,3,12,208,8,12,1,12,1,12,1,13,1,13,1,13,1,13,3,13,216,8,13,1,13,1,13,1,
14,1,14,1,14,1,14,3,14,224,8,14,1,14,1,14,1,14,3,14,229,8,14,1,14,1,14,1,
14,3,14,234,8,14,1,14,1,14,1,14,1,14,3,14,240,8,14,1,14,1,14,1,14,1,14,3,
14,246,8,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,257,8,15,1,
15,1,15,1,16,1,16,1,16,3,16,264,8,16,1,17,1,17,1,18,1,18,1,19,1,19,1,19,
1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,282,8,19,1,19,1,19,3,19,
286,8,19,1,19,3,19,289,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,324,8,19,10,19,12,19,
327,9,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,337,8,20,1,20,1,20,
1,20,3,20,342,8,20,1,20,1,20,5,20,346,8,20,10,20,12,20,349,9,20,1,21,1,21,
1,21,1,21,1,21,1,21,5,21,357,8,21,10,21,12,21,360,9,21,1,21,0,8,2,6,14,16,
22,38,40,42,22,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
42,0,6,1,0,23,26,3,0,44,46,51,51,53,53,1,0,27,29,1,0,25,26,1,0,30,33,1,0,
34,35,399,0,44,1,0,0,0,2,53,1,0,0,0,4,62,1,0,0,0,6,76,1,0,0,0,8,90,1,0,0,
0,10,102,1,0,0,0,12,106,1,0,0,0,14,124,1,0,0,0,16,160,1,0,0,0,18,169,1,0,
0,0,20,178,1,0,0,0,22,189,1,0,0,0,24,199,1,0,0,0,26,211,1,0,0,0,28,219,1,
0,0,0,30,249,1,0,0,0,32,260,1,0,0,0,34,265,1,0,0,0,36,267,1,0,0,0,38,288,
1,0,0,0,40,341,1,0,0,0,42,350,1,0,0,0,44,45,3,2,1,0,45,46,5,0,0,1,46,1,1,
0,0,0,47,48,6,1,-1,0,48,54,3,4,2,0,49,54,3,12,6,0,50,51,3,10,5,0,51,52,5,
1,0,0,52,54,1,0,0,0,53,47,1,0,0,0,53,49,1,0,0,0,53,50,1,0,0,0,54,59,1,0,
0,0,55,56,10,4,0,0,56,58,3,2,1,5,57,55,1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,
0,59,60,1,0,0,0,60,3,1,0,0,0,61,59,1,0,0,0,62,63,5,2,0,0,63,67,5,52,0,0,
64,65,5,3,0,0,65,68,5,52,0,0,66,68,1,0,0,0,67,64,1,0,0,0,67,66,1,0,0,0,68,
69,1,0,0,0,69,72,5,4,0,0,70,73,3,6,3,0,71,73,1,0,0,0,72,70,1,0,0,0,72,71,
1,0,0,0,73,74,1,0,0,0,74,75,5,5,0,0,75,5,1,0,0,0,76,77,6,3,-1,0,77,78,3,
8,4,0,78,83,1,0,0,0,79,80,10,2,0,0,80,82,3,6,3,3,81,79,1,0,0,0,82,85,1,0,
0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,7,1,0,0,0,85,83,1,0,0,0,86,91,5,6,0,0,
87,91,5,7,0,0,88,91,5,8,0,0,89,91,1,0,0,0,90,86,1,0,0,0,90,87,1,0,0,0,90,
88,1,0,0,0,90,89,1,0,0,0,91,94,1,0,0,0,92,95,5,9,0,0,93,95,1,0,0,0,94,92,
1,0,0,0,94,93,1,0,0,0,95,100,1,0,0,0,96,101,3,12,6,0,97,98,3,10,5,0,98,99,
5,1,0,0,99,101,1,0,0,0,100,96,1,0,0,0,100,97,1,0,0,0,101,9,1,0,0,0,102,103,
5,52,0,0,103,104,5,10,0,0,104,105,3,38,19,0,105,11,1,0,0,0,106,107,5,11,
0,0,107,115,5,52,0,0,108,111,5,12,0,0,109,112,3,14,7,0,110,112,1,0,0,0,111,
109,1,0,0,0,111,110,1,0,0,0,112,113,1,0,0,0,113,116,5,13,0,0,114,116,1,0,
0,0,115,108,1,0,0,0,115,114,1,0,0,0,116,117,1,0,0,0,117,120,5,4,0,0,118,
121,3,16,8,0,119,121,1,0,0,0,120,118,1,0,0,0,120,119,1,0,0,0,121,122,1,0,
0,0,122,123,5,5,0,0,123,13,1,0,0,0,124,125,6,7,-1,0,125,126,5,52,0,0,126,
132,1,0,0,0,127,128,10,2,0,0,128,129,5,14,0,0,129,131,3,14,7,3,130,127,1,
0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,15,1,0,0,0,134,
132,1,0,0,0,135,139,6,8,-1,0,136,140,3,10,5,0,137,140,3,38,19,0,138,140,
1,0,0,0,139,136,1,0,0,0,139,137,1,0,0,0,139,138,1,0,0,0,140,141,1,0,0,0,
141,161,5,1,0,0,142,161,3,18,9,0,143,161,3,28,14,0,144,161,3,30,15,0,145,
146,3,32,16,0,146,147,5,1,0,0,147,161,1,0,0,0,148,149,3,34,17,0,149,150,
5,1,0,0,150,161,1,0,0,0,151,152,3,36,18,0,152,153,5,1,0,0,153,161,1,0,0,
0,154,157,5,4,0,0,155,158,3,16,8,0,156,158,1,0,0,0,157,155,1,0,0,0,157,156,
1,0,0,0,158,159,1,0,0,0,159,161,5,5,0,0,160,135,1,0,0,0,160,142,1,0,0,0,
160,143,1,0,0,0,160,144,1,0,0,0,160,145,1,0,0,0,160,148,1,0,0,0,160,151,
1,0,0,0,160,154,1,0,0,0,161,166,1,0,0,0,162,163,10,9,0,0,163,165,3,16,8,
10,164,162,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,0,166,167,1,0,0,0,167,17,
1,0,0,0,168,166,1,0,0,0,169,172,3,20,10,0,170,173,3,22,11,0,171,173,1,0,
0,0,172,170,1,0,0,0,172,171,1,0,0,0,173,176,1,0,0,0,174,177,3,26,13,0,175,
177,1,0,0,0,176,174,1,0,0,0,176,175,1,0,0,0,177,19,1,0,0,0,178,179,5,15,
0,0,179,180,5,12,0,0,180,181,3,38,19,0,181,182,5,13,0,0,182,185,5,4,0,0,
183,186,3,16,8,0,184,186,1,0,0,0,185,183,1,0,0,0,185,184,1,0,0,0,186,187,
1,0,0,0,187,188,5,5,0,0,188,21,1,0,0,0,189,190,6,11,-1,0,190,191,3,24,12,
0,191,196,1,0,0,0,192,193,10,2,0,0,193,195,3,22,11,3,194,192,1,0,0,0,195,
198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,0,0,197,23,1,0,0,0,198,196,1,0,0,
0,199,200,5,16,0,0,200,201,5,15,0,0,201,202,5,12,0,0,202,203,3,38,19,0,203,
204,5,13,0,0,204,207,5,4,0,0,205,208,3,16,8,0,206,208,1,0,0,0,207,205,1,
0,0,0,207,206,1,0,0,0,208,209,1,0,0,0,209,210,5,5,0,0,210,25,1,0,0,0,211,
212,5,16,0,0,212,215,5,4,0,0,213,216,3,16,8,0,214,216,1,0,0,0,215,213,1,
0,0,0,215,214,1,0,0,0,216,217,1,0,0,0,217,218,5,5,0,0,218,27,1,0,0,0,219,
220,5,17,0,0,220,239,5,12,0,0,221,224,3,38,19,0,222,224,1,0,0,0,223,221,
1,0,0,0,223,222,1,0,0,0,224,225,1,0,0,0,225,228,5,1,0,0,226,229,3,38,19,
0,227,229,1,0,0,0,228,226,1,0,0,0,228,227,1,0,0,0,229,230,1,0,0,0,230,233,
5,1,0,0,231,234,3,38,19,0,232,234,1,0,0,0,233,231,1,0,0,0,233,232,1,0,0,
0,234,240,1,0,0,0,235,236,3,38,19,0,236,237,5,18,0,0,237,238,3,38,19,0,238,
240,1,0,0,0,239,223,1,0,0,0,239,235,1,0,0,0,240,241,1,0,0,0,241,242,5,13,
0,0,242,245,5,4,0,0,243,246,3,16,8,0,244,246,1,0,0,0,245,243,1,0,0,0,245,
244,1,0,0,0,246,247,1,0,0,0,247,248,5,5,0,0,248,29,1,0,0,0,249,250,5,19,
0,0,250,251,5,12,0,0,251,252,3,38,19,0,252,253,5,13,0,0,253,256,5,4,0,0,
254,257,3,16,8,0,255,257,1,0,0,0,256,254,1,0,0,0,256,255,1,0,0,0,257,258,
1,0,0,0,258,259,5,5,0,0,259,31,1,0,0,0,260,263,5,20,0,0,261,264,3,38,19,
0,262,264,1,0,0,0,263,261,1,0,0,0,263,262,1,0,0,0,264,33,1,0,0,0,265,266,
5,21,0,0,266,35,1,0,0,0,267,268,5,22,0,0,268,37,1,0,0,0,269,270,6,19,-1,
0,270,271,7,0,0,0,271,289,3,38,19,14,272,273,5,37,0,0,273,289,3,38,19,8,
274,275,5,43,0,0,275,282,5,52,0,0,276,282,5,52,0,0,277,278,5,12,0,0,278,
279,3,38,19,0,279,280,5,13,0,0,280,282,1,0,0,0,281,274,1,0,0,0,281,276,1,
0,0,0,281,277,1,0,0,0,282,285,1,0,0,0,283,286,3,40,20,0,284,286,1,0,0,0,
285,283,1,0,0,0,285,284,1,0,0,0,286,289,1,0,0,0,287,289,7,1,0,0,288,269,
1,0,0,0,288,272,1,0,0,0,288,281,1,0,0,0,288,287,1,0,0,0,289,325,1,0,0,0,
290,291,10,13,0,0,291,292,7,2,0,0,292,324,3,38,19,14,293,294,10,12,0,0,294,
295,7,3,0,0,295,324,3,38,19,13,296,297,10,11,0,0,297,298,7,4,0,0,298,324,
3,38,19,12,299,300,10,10,0,0,300,301,7,5,0,0,301,324,3,38,19,11,302,303,
10,9,0,0,303,304,5,36,0,0,304,324,3,38,19,10,305,306,10,7,0,0,306,307,5,
38,0,0,307,324,3,38,19,8,308,309,10,6,0,0,309,310,5,39,0,0,310,324,3,38,
19,7,311,312,10,5,0,0,312,313,5,40,0,0,313,324,3,38,19,6,314,315,10,4,0,
0,315,316,5,41,0,0,316,317,3,38,19,0,317,318,5,42,0,0,318,319,3,38,19,4,
319,324,1,0,0,0,320,321,10,1,0,0,321,322,5,10,0,0,322,324,3,38,19,1,323,
290,1,0,0,0,323,293,1,0,0,0,323,296,1,0,0,0,323,299,1,0,0,0,323,302,1,0,
0,0,323,305,1,0,0,0,323,308,1,0,0,0,323,311,1,0,0,0,323,314,1,0,0,0,323,
320,1,0,0,0,324,327,1,0,0,0,325,323,1,0,0,0,325,326,1,0,0,0,326,39,1,0,0,
0,327,325,1,0,0,0,328,329,6,20,-1,0,329,330,5,47,0,0,330,331,3,38,19,0,331,
332,5,48,0,0,332,342,1,0,0,0,333,336,5,12,0,0,334,337,3,42,21,0,335,337,
1,0,0,0,336,334,1,0,0,0,336,335,1,0,0,0,337,338,1,0,0,0,338,342,5,13,0,0,
339,340,5,49,0,0,340,342,5,52,0,0,341,328,1,0,0,0,341,333,1,0,0,0,341,339,
1,0,0,0,342,347,1,0,0,0,343,344,10,4,0,0,344,346,3,40,20,5,345,343,1,0,0,
0,346,349,1,0,0,0,347,345,1,0,0,0,347,348,1,0,0,0,348,41,1,0,0,0,349,347,
1,0,0,0,350,351,6,21,-1,0,351,352,3,38,19,0,352,358,1,0,0,0,353,354,10,2,
0,0,354,355,5,14,0,0,355,357,3,42,21,3,356,353,1,0,0,0,357,360,1,0,0,0,358,
356,1,0,0,0,358,359,1,0,0,0,359,43,1,0,0,0,360,358,1,0,0,0,38,53,59,67,72,
83,90,94,100,111,115,120,132,139,157,160,166,172,176,185,196,207,215,223,
228,233,239,245,256,263,281,285,288,323,325,336,341,347,358];


const atn = new antlr4.atn.ATNDeserializer().deserialize(serializedATN);

const decisionsToDFA = atn.decisionToState.map( (ds, index) => new antlr4.dfa.DFA(ds, index) );

const sharedContextCache = new antlr4.atn.PredictionContextCache();

export default class ScriptGrammarParser extends antlr4.Parser {

    static grammarFileName = "ScriptGrammar.g4";
    static literalNames = [ null, "';'", "'class'", "'extend'", "'{'", "'}'", 
                            "'private'", "'protected'", "'public'", "'static'", 
                            "'='", "'def'", "'('", "')'", "','", "'if'", 
                            "'else'", "'for'", "'in'", "'while'", "'return'", 
                            "'continue'", "'break'", "'!'", "'~'", "'+'", 
                            "'-'", "'*'", "'/'", "'%'", "'>='", "'<='", 
                            "'>'", "'<'", "'=='", "'!='", "'&'", "'^'", 
                            "'|'", "'&&'", "'||'", "'?'", "':'", "'new'", 
                            "'true'", "'false'", "'null'", "'['", "']'", 
                            "'.'" ];
    static symbolicNames = [ null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, null, null, null, null, null, null, 
                             null, null, "WS", "NUMBER", "ID", "STRING", 
                             "BLOCK_COMMENT", "LINE_COMMENT" ];
    static ruleNames = [ "prog", "decls", "declClass", "declMembers", "declMember", 
                         "declVar", "declFunction", "declArgs", "stmts", 
                         "stmtCondition", "stmtIf", "stmtElseIfs", "stmtElseIf", 
                         "stmtElse", "stmtFor", "stmtWhile", "stmtReturn", 
                         "stmtContinue", "stmtBreak", "expr", "accs", "args" ];

    constructor(input) {
        super(input);
        this._interp = new antlr4.atn.ParserATNSimulator(this, atn, decisionsToDFA, sharedContextCache);
        this.ruleNames = ScriptGrammarParser.ruleNames;
        this.literalNames = ScriptGrammarParser.literalNames;
        this.symbolicNames = ScriptGrammarParser.symbolicNames;
    }

    sempred(localctx, ruleIndex, predIndex) {
    	switch(ruleIndex) {
    	case 1:
    	    		return this.decls_sempred(localctx, predIndex);
    	case 3:
    	    		return this.declMembers_sempred(localctx, predIndex);
    	case 7:
    	    		return this.declArgs_sempred(localctx, predIndex);
    	case 8:
    	    		return this.stmts_sempred(localctx, predIndex);
    	case 11:
    	    		return this.stmtElseIfs_sempred(localctx, predIndex);
    	case 19:
    	    		return this.expr_sempred(localctx, predIndex);
    	case 20:
    	    		return this.accs_sempred(localctx, predIndex);
    	case 21:
    	    		return this.args_sempred(localctx, predIndex);
        default:
            throw "No predicate with index:" + ruleIndex;
       }
    }

    decls_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 0:
    			return this.precpred(this._ctx, 4);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    declMembers_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 1:
    			return this.precpred(this._ctx, 2);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    declArgs_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 2:
    			return this.precpred(this._ctx, 2);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    stmts_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 3:
    			return this.precpred(this._ctx, 9);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    stmtElseIfs_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 4:
    			return this.precpred(this._ctx, 2);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    expr_sempred(localctx, predIndex) {
    	switch(predIndex) {
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
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    accs_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 15:
    			return this.precpred(this._ctx, 4);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };

    args_sempred(localctx, predIndex) {
    	switch(predIndex) {
    		case 16:
    			return this.precpred(this._ctx, 2);
    		default:
    			throw "No predicate with index:" + predIndex;
    	}
    };




	prog() {
	    let localctx = new ProgContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 0, ScriptGrammarParser.RULE_prog);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 44;
	        this.decls(0);
	        this.state = 45;
	        this.match(ScriptGrammarParser.EOF);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


	decls(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new DeclsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 2;
	    this.enterRecursionRule(localctx, 2, ScriptGrammarParser.RULE_decls, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 53;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 2:
	            this.state = 48;
	            this.declClass();
	            break;
	        case 11:
	            this.state = 49;
	            this.declFunction();
	            break;
	        case 52:
	            this.state = 50;
	            this.declVar();
	            this.state = 51;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 59;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,1,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new DeclsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_decls);
	                this.state = 55;
	                if (!( this.precpred(this._ctx, 4))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 4)");
	                }
	                this.state = 56;
	                this.decls(5); 
	            }
	            this.state = 61;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,1,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	declClass() {
	    let localctx = new DeclClassContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 4, ScriptGrammarParser.RULE_declClass);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 62;
	        this.match(ScriptGrammarParser.T__1);
	        this.state = 63;
	        this.match(ScriptGrammarParser.ID);
	        this.state = 67;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 3:
	            this.state = 64;
	            this.match(ScriptGrammarParser.T__2);
	            this.state = 65;
	            this.match(ScriptGrammarParser.ID);
	            break;
	        case 4:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 69;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 72;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 6:
	        case 7:
	        case 8:
	        case 9:
	        case 11:
	        case 52:
	            this.state = 70;
	            this.declMembers(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 74;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


	declMembers(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new DeclMembersContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 6;
	    this.enterRecursionRule(localctx, 6, ScriptGrammarParser.RULE_declMembers, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 77;
	        this.declMember();
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 83;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,4,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new DeclMembersContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_declMembers);
	                this.state = 79;
	                if (!( this.precpred(this._ctx, 2))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 2)");
	                }
	                this.state = 80;
	                this.declMembers(3); 
	            }
	            this.state = 85;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,4,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	declMember() {
	    let localctx = new DeclMemberContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 8, ScriptGrammarParser.RULE_declMember);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 90;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 6:
	            this.state = 86;
	            this.match(ScriptGrammarParser.T__5);
	            break;
	        case 7:
	            this.state = 87;
	            this.match(ScriptGrammarParser.T__6);
	            break;
	        case 8:
	            this.state = 88;
	            this.match(ScriptGrammarParser.T__7);
	            break;
	        case 9:
	        case 11:
	        case 52:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 94;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 9:
	            this.state = 92;
	            this.match(ScriptGrammarParser.T__8);
	            break;
	        case 11:
	        case 52:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 100;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 11:
	            this.state = 96;
	            this.declFunction();
	            break;
	        case 52:
	            this.state = 97;
	            this.declVar();
	            this.state = 98;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	declVar() {
	    let localctx = new DeclVarContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 10, ScriptGrammarParser.RULE_declVar);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 102;
	        this.match(ScriptGrammarParser.ID);
	        this.state = 103;
	        this.match(ScriptGrammarParser.T__9);
	        this.state = 104;
	        this.expr(0);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	declFunction() {
	    let localctx = new DeclFunctionContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 12, ScriptGrammarParser.RULE_declFunction);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 106;
	        this.match(ScriptGrammarParser.T__10);
	        this.state = 107;
	        this.match(ScriptGrammarParser.ID);
	        this.state = 115;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 12:
	            this.state = 108;
	            this.match(ScriptGrammarParser.T__11);
	            this.state = 111;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 52:
	                this.state = 109;
	                this.declArgs(0);
	                break;
	            case 13:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 113;
	            this.match(ScriptGrammarParser.T__12);
	            break;
	        case 4:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 117;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 120;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 118;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 122;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


	declArgs(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new DeclArgsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 14;
	    this.enterRecursionRule(localctx, 14, ScriptGrammarParser.RULE_declArgs, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 125;
	        this.match(ScriptGrammarParser.ID);
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 132;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,11,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new DeclArgsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_declArgs);
	                this.state = 127;
	                if (!( this.precpred(this._ctx, 2))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 2)");
	                }
	                this.state = 128;
	                this.match(ScriptGrammarParser.T__13);
	                this.state = 129;
	                this.declArgs(3); 
	            }
	            this.state = 134;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,11,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}


	stmts(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new StmtsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 16;
	    this.enterRecursionRule(localctx, 16, ScriptGrammarParser.RULE_stmts, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 160;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 12:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 139;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,12,this._ctx);
	            switch(la_) {
	            case 1:
	                this.state = 136;
	                this.declVar();
	                break;

	            case 2:
	                this.state = 137;
	                this.expr(0);
	                break;

	            case 3:
	                break;

	            }
	            this.state = 141;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        case 15:
	            this.state = 142;
	            this.stmtCondition();
	            break;
	        case 17:
	            this.state = 143;
	            this.stmtFor();
	            break;
	        case 19:
	            this.state = 144;
	            this.stmtWhile();
	            break;
	        case 20:
	            this.state = 145;
	            this.stmtReturn();
	            this.state = 146;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        case 21:
	            this.state = 148;
	            this.stmtContinue();
	            this.state = 149;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        case 22:
	            this.state = 151;
	            this.stmtBreak();
	            this.state = 152;
	            this.match(ScriptGrammarParser.T__0);
	            break;
	        case 4:
	            this.state = 154;
	            this.match(ScriptGrammarParser.T__3);
	            this.state = 157;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 1:
	            case 4:
	            case 12:
	            case 15:
	            case 17:
	            case 19:
	            case 20:
	            case 21:
	            case 22:
	            case 23:
	            case 24:
	            case 25:
	            case 26:
	            case 37:
	            case 43:
	            case 44:
	            case 45:
	            case 46:
	            case 51:
	            case 52:
	            case 53:
	                this.state = 155;
	                this.stmts(0);
	                break;
	            case 5:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 159;
	            this.match(ScriptGrammarParser.T__4);
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 166;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,15,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new StmtsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_stmts);
	                this.state = 162;
	                if (!( this.precpred(this._ctx, 9))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 9)");
	                }
	                this.state = 163;
	                this.stmts(10); 
	            }
	            this.state = 168;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,15,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	stmtCondition() {
	    let localctx = new StmtConditionContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 18, ScriptGrammarParser.RULE_stmtCondition);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 169;
	        this.stmtIf();
	        this.state = 172;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,16,this._ctx);
	        switch(la_) {
	        case 1:
	            this.state = 170;
	            this.stmtElseIfs(0);
	            break;

	        case 2:
	            break;

	        }
	        this.state = 176;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,17,this._ctx);
	        switch(la_) {
	        case 1:
	            this.state = 174;
	            this.stmtElse();
	            break;

	        case 2:
	            break;

	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtIf() {
	    let localctx = new StmtIfContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 20, ScriptGrammarParser.RULE_stmtIf);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 178;
	        this.match(ScriptGrammarParser.T__14);
	        this.state = 179;
	        this.match(ScriptGrammarParser.T__11);
	        this.state = 180;
	        this.expr(0);
	        this.state = 181;
	        this.match(ScriptGrammarParser.T__12);
	        this.state = 182;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 185;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 183;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 187;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


	stmtElseIfs(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new StmtElseIfsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 22;
	    this.enterRecursionRule(localctx, 22, ScriptGrammarParser.RULE_stmtElseIfs, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 190;
	        this.stmtElseIf();
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 196;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,19,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new StmtElseIfsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_stmtElseIfs);
	                this.state = 192;
	                if (!( this.precpred(this._ctx, 2))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 2)");
	                }
	                this.state = 193;
	                this.stmtElseIfs(3); 
	            }
	            this.state = 198;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,19,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}



	stmtElseIf() {
	    let localctx = new StmtElseIfContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 24, ScriptGrammarParser.RULE_stmtElseIf);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 199;
	        this.match(ScriptGrammarParser.T__15);
	        this.state = 200;
	        this.match(ScriptGrammarParser.T__14);
	        this.state = 201;
	        this.match(ScriptGrammarParser.T__11);
	        this.state = 202;
	        this.expr(0);
	        this.state = 203;
	        this.match(ScriptGrammarParser.T__12);
	        this.state = 204;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 207;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 205;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 209;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtElse() {
	    let localctx = new StmtElseContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 26, ScriptGrammarParser.RULE_stmtElse);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 211;
	        this.match(ScriptGrammarParser.T__15);
	        this.state = 212;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 215;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 213;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 217;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtFor() {
	    let localctx = new StmtForContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 28, ScriptGrammarParser.RULE_stmtFor);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 219;
	        this.match(ScriptGrammarParser.T__16);
	        this.state = 220;
	        this.match(ScriptGrammarParser.T__11);
	        this.state = 239;
	        this._errHandler.sync(this);
	        var la_ = this._interp.adaptivePredict(this._input,25,this._ctx);
	        switch(la_) {
	        case 1:
	            this.state = 223;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 12:
	            case 23:
	            case 24:
	            case 25:
	            case 26:
	            case 37:
	            case 43:
	            case 44:
	            case 45:
	            case 46:
	            case 51:
	            case 52:
	            case 53:
	                this.state = 221;
	                this.expr(0);
	                break;
	            case 1:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 225;
	            this.match(ScriptGrammarParser.T__0);
	            this.state = 228;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 12:
	            case 23:
	            case 24:
	            case 25:
	            case 26:
	            case 37:
	            case 43:
	            case 44:
	            case 45:
	            case 46:
	            case 51:
	            case 52:
	            case 53:
	                this.state = 226;
	                this.expr(0);
	                break;
	            case 1:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 230;
	            this.match(ScriptGrammarParser.T__0);
	            this.state = 233;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 12:
	            case 23:
	            case 24:
	            case 25:
	            case 26:
	            case 37:
	            case 43:
	            case 44:
	            case 45:
	            case 46:
	            case 51:
	            case 52:
	            case 53:
	                this.state = 231;
	                this.expr(0);
	                break;
	            case 13:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            break;

	        case 2:
	            this.state = 235;
	            this.expr(0);
	            this.state = 236;
	            this.match(ScriptGrammarParser.T__17);
	            this.state = 237;
	            this.expr(0);
	            break;

	        }
	        this.state = 241;
	        this.match(ScriptGrammarParser.T__12);
	        this.state = 242;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 245;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 243;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 247;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtWhile() {
	    let localctx = new StmtWhileContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 30, ScriptGrammarParser.RULE_stmtWhile);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 249;
	        this.match(ScriptGrammarParser.T__18);
	        this.state = 250;
	        this.match(ScriptGrammarParser.T__11);
	        this.state = 251;
	        this.expr(0);
	        this.state = 252;
	        this.match(ScriptGrammarParser.T__12);
	        this.state = 253;
	        this.match(ScriptGrammarParser.T__3);
	        this.state = 256;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 1:
	        case 4:
	        case 12:
	        case 15:
	        case 17:
	        case 19:
	        case 20:
	        case 21:
	        case 22:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 254;
	            this.stmts(0);
	            break;
	        case 5:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this.state = 258;
	        this.match(ScriptGrammarParser.T__4);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtReturn() {
	    let localctx = new StmtReturnContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 32, ScriptGrammarParser.RULE_stmtReturn);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 260;
	        this.match(ScriptGrammarParser.T__19);
	        this.state = 263;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 12:
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	        case 37:
	        case 43:
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 52:
	        case 53:
	            this.state = 261;
	            this.expr(0);
	            break;
	        case 1:
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtContinue() {
	    let localctx = new StmtContinueContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 34, ScriptGrammarParser.RULE_stmtContinue);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 265;
	        this.match(ScriptGrammarParser.T__20);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}



	stmtBreak() {
	    let localctx = new StmtBreakContext(this, this._ctx, this.state);
	    this.enterRule(localctx, 36, ScriptGrammarParser.RULE_stmtBreak);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 267;
	        this.match(ScriptGrammarParser.T__21);
	    } catch (re) {
	    	if(re instanceof antlr4.error.RecognitionException) {
		        localctx.exception = re;
		        this._errHandler.reportError(this, re);
		        this._errHandler.recover(this, re);
		    } else {
		    	throw re;
		    }
	    } finally {
	        this.exitRule();
	    }
	    return localctx;
	}


	expr(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new ExprContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 38;
	    this.enterRecursionRule(localctx, 38, ScriptGrammarParser.RULE_expr, _p);
	    var _la = 0;
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 288;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 23:
	        case 24:
	        case 25:
	        case 26:
	            this.state = 270;
	            _la = this._input.LA(1);
	            if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 125829120) !== 0))) {
	            this._errHandler.recoverInline(this);
	            }
	            else {
	            	this._errHandler.reportMatch(this);
	                this.consume();
	            }
	            this.state = 271;
	            this.expr(14);
	            break;
	        case 37:
	            this.state = 272;
	            this.match(ScriptGrammarParser.T__36);
	            this.state = 273;
	            this.expr(8);
	            break;
	        case 12:
	        case 43:
	        case 52:
	            this.state = 281;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 43:
	                this.state = 274;
	                this.match(ScriptGrammarParser.T__42);
	                this.state = 275;
	                this.match(ScriptGrammarParser.ID);
	                break;
	            case 52:
	                this.state = 276;
	                this.match(ScriptGrammarParser.ID);
	                break;
	            case 12:
	                this.state = 277;
	                this.match(ScriptGrammarParser.T__11);
	                this.state = 278;
	                this.expr(0);
	                this.state = 279;
	                this.match(ScriptGrammarParser.T__12);
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 285;
	            this._errHandler.sync(this);
	            var la_ = this._interp.adaptivePredict(this._input,30,this._ctx);
	            switch(la_) {
	            case 1:
	                this.state = 283;
	                this.accs(0);
	                break;

	            case 2:
	                break;

	            }
	            break;
	        case 44:
	        case 45:
	        case 46:
	        case 51:
	        case 53:
	            this.state = 287;
	            _la = this._input.LA(1);
	            if(!(((((_la - 44)) & ~0x1f) === 0 && ((1 << (_la - 44)) & 647) !== 0))) {
	            this._errHandler.recoverInline(this);
	            }
	            else {
	            	this._errHandler.reportMatch(this);
	                this.consume();
	            }
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 325;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,33,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                this.state = 323;
	                this._errHandler.sync(this);
	                var la_ = this._interp.adaptivePredict(this._input,32,this._ctx);
	                switch(la_) {
	                case 1:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 290;
	                    if (!( this.precpred(this._ctx, 13))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 13)");
	                    }
	                    this.state = 291;
	                    _la = this._input.LA(1);
	                    if(!((((_la) & ~0x1f) === 0 && ((1 << _la) & 939524096) !== 0))) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 292;
	                    this.expr(14);
	                    break;

	                case 2:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 293;
	                    if (!( this.precpred(this._ctx, 12))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 12)");
	                    }
	                    this.state = 294;
	                    _la = this._input.LA(1);
	                    if(!(_la===25 || _la===26)) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 295;
	                    this.expr(13);
	                    break;

	                case 3:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 296;
	                    if (!( this.precpred(this._ctx, 11))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 11)");
	                    }
	                    this.state = 297;
	                    _la = this._input.LA(1);
	                    if(!(((((_la - 30)) & ~0x1f) === 0 && ((1 << (_la - 30)) & 15) !== 0))) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 298;
	                    this.expr(12);
	                    break;

	                case 4:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 299;
	                    if (!( this.precpred(this._ctx, 10))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 10)");
	                    }
	                    this.state = 300;
	                    _la = this._input.LA(1);
	                    if(!(_la===34 || _la===35)) {
	                    this._errHandler.recoverInline(this);
	                    }
	                    else {
	                    	this._errHandler.reportMatch(this);
	                        this.consume();
	                    }
	                    this.state = 301;
	                    this.expr(11);
	                    break;

	                case 5:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 302;
	                    if (!( this.precpred(this._ctx, 9))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 9)");
	                    }
	                    this.state = 303;
	                    this.match(ScriptGrammarParser.T__35);
	                    this.state = 304;
	                    this.expr(10);
	                    break;

	                case 6:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 305;
	                    if (!( this.precpred(this._ctx, 7))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 7)");
	                    }
	                    this.state = 306;
	                    this.match(ScriptGrammarParser.T__37);
	                    this.state = 307;
	                    this.expr(8);
	                    break;

	                case 7:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 308;
	                    if (!( this.precpred(this._ctx, 6))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 6)");
	                    }
	                    this.state = 309;
	                    this.match(ScriptGrammarParser.T__38);
	                    this.state = 310;
	                    this.expr(7);
	                    break;

	                case 8:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 311;
	                    if (!( this.precpred(this._ctx, 5))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 5)");
	                    }
	                    this.state = 312;
	                    this.match(ScriptGrammarParser.T__39);
	                    this.state = 313;
	                    this.expr(6);
	                    break;

	                case 9:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 314;
	                    if (!( this.precpred(this._ctx, 4))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 4)");
	                    }
	                    this.state = 315;
	                    this.match(ScriptGrammarParser.T__40);
	                    this.state = 316;
	                    this.expr(0);
	                    this.state = 317;
	                    this.match(ScriptGrammarParser.T__41);
	                    this.state = 318;
	                    this.expr(4);
	                    break;

	                case 10:
	                    localctx = new ExprContext(this, _parentctx, _parentState);
	                    this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_expr);
	                    this.state = 320;
	                    if (!( this.precpred(this._ctx, 1))) {
	                        throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 1)");
	                    }
	                    this.state = 321;
	                    this.match(ScriptGrammarParser.T__9);
	                    this.state = 322;
	                    this.expr(1);
	                    break;

	                } 
	            }
	            this.state = 327;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,33,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}


	accs(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new AccsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 40;
	    this.enterRecursionRule(localctx, 40, ScriptGrammarParser.RULE_accs, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 341;
	        this._errHandler.sync(this);
	        switch(this._input.LA(1)) {
	        case 47:
	            this.state = 329;
	            this.match(ScriptGrammarParser.T__46);
	            this.state = 330;
	            this.expr(0);
	            this.state = 331;
	            this.match(ScriptGrammarParser.T__47);
	            break;
	        case 12:
	            this.state = 333;
	            this.match(ScriptGrammarParser.T__11);
	            this.state = 336;
	            this._errHandler.sync(this);
	            switch(this._input.LA(1)) {
	            case 12:
	            case 23:
	            case 24:
	            case 25:
	            case 26:
	            case 37:
	            case 43:
	            case 44:
	            case 45:
	            case 46:
	            case 51:
	            case 52:
	            case 53:
	                this.state = 334;
	                this.args(0);
	                break;
	            case 13:
	                break;
	            default:
	                throw new antlr4.error.NoViableAltException(this);
	            }
	            this.state = 338;
	            this.match(ScriptGrammarParser.T__12);
	            break;
	        case 49:
	            this.state = 339;
	            this.match(ScriptGrammarParser.T__48);
	            this.state = 340;
	            this.match(ScriptGrammarParser.ID);
	            break;
	        default:
	            throw new antlr4.error.NoViableAltException(this);
	        }
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 347;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,36,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new AccsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_accs);
	                this.state = 343;
	                if (!( this.precpred(this._ctx, 4))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 4)");
	                }
	                this.state = 344;
	                this.accs(5); 
	            }
	            this.state = 349;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,36,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}


	args(_p) {
		if(_p===undefined) {
		    _p = 0;
		}
	    const _parentctx = this._ctx;
	    const _parentState = this.state;
	    let localctx = new ArgsContext(this, this._ctx, _parentState);
	    let _prevctx = localctx;
	    const _startState = 42;
	    this.enterRecursionRule(localctx, 42, ScriptGrammarParser.RULE_args, _p);
	    try {
	        this.enterOuterAlt(localctx, 1);
	        this.state = 351;
	        this.expr(0);
	        this._ctx.stop = this._input.LT(-1);
	        this.state = 358;
	        this._errHandler.sync(this);
	        var _alt = this._interp.adaptivePredict(this._input,37,this._ctx)
	        while(_alt!=2 && _alt!=antlr4.atn.ATN.INVALID_ALT_NUMBER) {
	            if(_alt===1) {
	                if(this._parseListeners!==null) {
	                    this.triggerExitRuleEvent();
	                }
	                _prevctx = localctx;
	                localctx = new ArgsContext(this, _parentctx, _parentState);
	                this.pushNewRecursionContext(localctx, _startState, ScriptGrammarParser.RULE_args);
	                this.state = 353;
	                if (!( this.precpred(this._ctx, 2))) {
	                    throw new antlr4.error.FailedPredicateException(this, "this.precpred(this._ctx, 2)");
	                }
	                this.state = 354;
	                this.match(ScriptGrammarParser.T__13);
	                this.state = 355;
	                this.args(3); 
	            }
	            this.state = 360;
	            this._errHandler.sync(this);
	            _alt = this._interp.adaptivePredict(this._input,37,this._ctx);
	        }

	    } catch( error) {
	        if(error instanceof antlr4.error.RecognitionException) {
		        localctx.exception = error;
		        this._errHandler.reportError(this, error);
		        this._errHandler.recover(this, error);
		    } else {
		    	throw error;
		    }
	    } finally {
	        this.unrollRecursionContexts(_parentctx)
	    }
	    return localctx;
	}


}

ScriptGrammarParser.EOF = antlr4.Token.EOF;
ScriptGrammarParser.T__0 = 1;
ScriptGrammarParser.T__1 = 2;
ScriptGrammarParser.T__2 = 3;
ScriptGrammarParser.T__3 = 4;
ScriptGrammarParser.T__4 = 5;
ScriptGrammarParser.T__5 = 6;
ScriptGrammarParser.T__6 = 7;
ScriptGrammarParser.T__7 = 8;
ScriptGrammarParser.T__8 = 9;
ScriptGrammarParser.T__9 = 10;
ScriptGrammarParser.T__10 = 11;
ScriptGrammarParser.T__11 = 12;
ScriptGrammarParser.T__12 = 13;
ScriptGrammarParser.T__13 = 14;
ScriptGrammarParser.T__14 = 15;
ScriptGrammarParser.T__15 = 16;
ScriptGrammarParser.T__16 = 17;
ScriptGrammarParser.T__17 = 18;
ScriptGrammarParser.T__18 = 19;
ScriptGrammarParser.T__19 = 20;
ScriptGrammarParser.T__20 = 21;
ScriptGrammarParser.T__21 = 22;
ScriptGrammarParser.T__22 = 23;
ScriptGrammarParser.T__23 = 24;
ScriptGrammarParser.T__24 = 25;
ScriptGrammarParser.T__25 = 26;
ScriptGrammarParser.T__26 = 27;
ScriptGrammarParser.T__27 = 28;
ScriptGrammarParser.T__28 = 29;
ScriptGrammarParser.T__29 = 30;
ScriptGrammarParser.T__30 = 31;
ScriptGrammarParser.T__31 = 32;
ScriptGrammarParser.T__32 = 33;
ScriptGrammarParser.T__33 = 34;
ScriptGrammarParser.T__34 = 35;
ScriptGrammarParser.T__35 = 36;
ScriptGrammarParser.T__36 = 37;
ScriptGrammarParser.T__37 = 38;
ScriptGrammarParser.T__38 = 39;
ScriptGrammarParser.T__39 = 40;
ScriptGrammarParser.T__40 = 41;
ScriptGrammarParser.T__41 = 42;
ScriptGrammarParser.T__42 = 43;
ScriptGrammarParser.T__43 = 44;
ScriptGrammarParser.T__44 = 45;
ScriptGrammarParser.T__45 = 46;
ScriptGrammarParser.T__46 = 47;
ScriptGrammarParser.T__47 = 48;
ScriptGrammarParser.T__48 = 49;
ScriptGrammarParser.WS = 50;
ScriptGrammarParser.NUMBER = 51;
ScriptGrammarParser.ID = 52;
ScriptGrammarParser.STRING = 53;
ScriptGrammarParser.BLOCK_COMMENT = 54;
ScriptGrammarParser.LINE_COMMENT = 55;

ScriptGrammarParser.RULE_prog = 0;
ScriptGrammarParser.RULE_decls = 1;
ScriptGrammarParser.RULE_declClass = 2;
ScriptGrammarParser.RULE_declMembers = 3;
ScriptGrammarParser.RULE_declMember = 4;
ScriptGrammarParser.RULE_declVar = 5;
ScriptGrammarParser.RULE_declFunction = 6;
ScriptGrammarParser.RULE_declArgs = 7;
ScriptGrammarParser.RULE_stmts = 8;
ScriptGrammarParser.RULE_stmtCondition = 9;
ScriptGrammarParser.RULE_stmtIf = 10;
ScriptGrammarParser.RULE_stmtElseIfs = 11;
ScriptGrammarParser.RULE_stmtElseIf = 12;
ScriptGrammarParser.RULE_stmtElse = 13;
ScriptGrammarParser.RULE_stmtFor = 14;
ScriptGrammarParser.RULE_stmtWhile = 15;
ScriptGrammarParser.RULE_stmtReturn = 16;
ScriptGrammarParser.RULE_stmtContinue = 17;
ScriptGrammarParser.RULE_stmtBreak = 18;
ScriptGrammarParser.RULE_expr = 19;
ScriptGrammarParser.RULE_accs = 20;
ScriptGrammarParser.RULE_args = 21;

class ProgContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_prog;
    }

	decls() {
	    return this.getTypedRuleContext(DeclsContext,0);
	};

	EOF() {
	    return this.getToken(ScriptGrammarParser.EOF, 0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterProg(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitProg(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitProg(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_decls;
    }

	declClass() {
	    return this.getTypedRuleContext(DeclClassContext,0);
	};

	declFunction() {
	    return this.getTypedRuleContext(DeclFunctionContext,0);
	};

	declVar() {
	    return this.getTypedRuleContext(DeclVarContext,0);
	};

	decls = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(DeclsContext);
	    } else {
	        return this.getTypedRuleContext(DeclsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDecls(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDecls(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDecls(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclClassContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declClass;
    }

	ID = function(i) {
		if(i===undefined) {
			i = null;
		}
	    if(i===null) {
	        return this.getTokens(ScriptGrammarParser.ID);
	    } else {
	        return this.getToken(ScriptGrammarParser.ID, i);
	    }
	};


	declMembers() {
	    return this.getTypedRuleContext(DeclMembersContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclClass(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclClass(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclClass(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclMembersContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declMembers;
    }

	declMember() {
	    return this.getTypedRuleContext(DeclMemberContext,0);
	};

	declMembers = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(DeclMembersContext);
	    } else {
	        return this.getTypedRuleContext(DeclMembersContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclMembers(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclMembers(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclMembers(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclMemberContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declMember;
    }

	declFunction() {
	    return this.getTypedRuleContext(DeclFunctionContext,0);
	};

	declVar() {
	    return this.getTypedRuleContext(DeclVarContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclMember(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclMember(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclMember(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclVarContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declVar;
    }

	ID() {
	    return this.getToken(ScriptGrammarParser.ID, 0);
	};

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclVar(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclVar(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclVar(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclFunctionContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declFunction;
    }

	ID() {
	    return this.getToken(ScriptGrammarParser.ID, 0);
	};

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	declArgs() {
	    return this.getTypedRuleContext(DeclArgsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclFunction(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclFunction(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclFunction(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class DeclArgsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_declArgs;
    }

	ID() {
	    return this.getToken(ScriptGrammarParser.ID, 0);
	};

	declArgs = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(DeclArgsContext);
	    } else {
	        return this.getTypedRuleContext(DeclArgsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterDeclArgs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitDeclArgs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitDeclArgs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmts;
    }

	declVar() {
	    return this.getTypedRuleContext(DeclVarContext,0);
	};

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	stmtCondition() {
	    return this.getTypedRuleContext(StmtConditionContext,0);
	};

	stmtFor() {
	    return this.getTypedRuleContext(StmtForContext,0);
	};

	stmtWhile() {
	    return this.getTypedRuleContext(StmtWhileContext,0);
	};

	stmtReturn() {
	    return this.getTypedRuleContext(StmtReturnContext,0);
	};

	stmtContinue() {
	    return this.getTypedRuleContext(StmtContinueContext,0);
	};

	stmtBreak() {
	    return this.getTypedRuleContext(StmtBreakContext,0);
	};

	stmts = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(StmtsContext);
	    } else {
	        return this.getTypedRuleContext(StmtsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmts(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmts(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmts(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtConditionContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtCondition;
    }

	stmtIf() {
	    return this.getTypedRuleContext(StmtIfContext,0);
	};

	stmtElseIfs() {
	    return this.getTypedRuleContext(StmtElseIfsContext,0);
	};

	stmtElse() {
	    return this.getTypedRuleContext(StmtElseContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtCondition(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtCondition(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtCondition(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtIfContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtIf;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtIf(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtIf(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtIf(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtElseIfsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtElseIfs;
    }

	stmtElseIf() {
	    return this.getTypedRuleContext(StmtElseIfContext,0);
	};

	stmtElseIfs = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(StmtElseIfsContext);
	    } else {
	        return this.getTypedRuleContext(StmtElseIfsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtElseIfs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtElseIfs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtElseIfs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtElseIfContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtElseIf;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtElseIf(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtElseIf(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtElseIf(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtElseContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtElse;
    }

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtElse(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtElse(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtElse(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtForContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtFor;
    }

	expr = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(ExprContext);
	    } else {
	        return this.getTypedRuleContext(ExprContext,i);
	    }
	};

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtFor(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtFor(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtFor(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtWhileContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtWhile;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	stmts() {
	    return this.getTypedRuleContext(StmtsContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtWhile(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtWhile(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtWhile(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtReturnContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtReturn;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtReturn(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtReturn(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtReturn(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtContinueContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtContinue;
    }


	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtContinue(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtContinue(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtContinue(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class StmtBreakContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_stmtBreak;
    }


	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterStmtBreak(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitStmtBreak(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitStmtBreak(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class ExprContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_expr;
    }

	expr = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(ExprContext);
	    } else {
	        return this.getTypedRuleContext(ExprContext,i);
	    }
	};

	ID() {
	    return this.getToken(ScriptGrammarParser.ID, 0);
	};

	accs() {
	    return this.getTypedRuleContext(AccsContext,0);
	};

	NUMBER() {
	    return this.getToken(ScriptGrammarParser.NUMBER, 0);
	};

	STRING() {
	    return this.getToken(ScriptGrammarParser.STRING, 0);
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterExpr(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitExpr(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitExpr(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class AccsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_accs;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	args() {
	    return this.getTypedRuleContext(ArgsContext,0);
	};

	ID() {
	    return this.getToken(ScriptGrammarParser.ID, 0);
	};

	accs = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(AccsContext);
	    } else {
	        return this.getTypedRuleContext(AccsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterAccs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitAccs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitAccs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}



class ArgsContext extends antlr4.ParserRuleContext {

    constructor(parser, parent, invokingState) {
        if(parent===undefined) {
            parent = null;
        }
        if(invokingState===undefined || invokingState===null) {
            invokingState = -1;
        }
        super(parent, invokingState);
        this.parser = parser;
        this.ruleIndex = ScriptGrammarParser.RULE_args;
    }

	expr() {
	    return this.getTypedRuleContext(ExprContext,0);
	};

	args = function(i) {
	    if(i===undefined) {
	        i = null;
	    }
	    if(i===null) {
	        return this.getTypedRuleContexts(ArgsContext);
	    } else {
	        return this.getTypedRuleContext(ArgsContext,i);
	    }
	};

	enterRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.enterArgs(this);
		}
	}

	exitRule(listener) {
	    if(listener instanceof ScriptGrammarListener ) {
	        listener.exitArgs(this);
		}
	}

	accept(visitor) {
	    if ( visitor instanceof ScriptGrammarVisitor ) {
	        return visitor.visitArgs(this);
	    } else {
	        return visitor.visitChildren(this);
	    }
	}


}




ScriptGrammarParser.ProgContext = ProgContext; 
ScriptGrammarParser.DeclsContext = DeclsContext; 
ScriptGrammarParser.DeclClassContext = DeclClassContext; 
ScriptGrammarParser.DeclMembersContext = DeclMembersContext; 
ScriptGrammarParser.DeclMemberContext = DeclMemberContext; 
ScriptGrammarParser.DeclVarContext = DeclVarContext; 
ScriptGrammarParser.DeclFunctionContext = DeclFunctionContext; 
ScriptGrammarParser.DeclArgsContext = DeclArgsContext; 
ScriptGrammarParser.StmtsContext = StmtsContext; 
ScriptGrammarParser.StmtConditionContext = StmtConditionContext; 
ScriptGrammarParser.StmtIfContext = StmtIfContext; 
ScriptGrammarParser.StmtElseIfsContext = StmtElseIfsContext; 
ScriptGrammarParser.StmtElseIfContext = StmtElseIfContext; 
ScriptGrammarParser.StmtElseContext = StmtElseContext; 
ScriptGrammarParser.StmtForContext = StmtForContext; 
ScriptGrammarParser.StmtWhileContext = StmtWhileContext; 
ScriptGrammarParser.StmtReturnContext = StmtReturnContext; 
ScriptGrammarParser.StmtContinueContext = StmtContinueContext; 
ScriptGrammarParser.StmtBreakContext = StmtBreakContext; 
ScriptGrammarParser.ExprContext = ExprContext; 
ScriptGrammarParser.AccsContext = AccsContext; 
ScriptGrammarParser.ArgsContext = ArgsContext; 
