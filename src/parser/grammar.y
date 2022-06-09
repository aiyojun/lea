



start: 
  multiImport
| multiImport multiLine
| multiLine
;


/** import */
multiImport:
  TermImport multiImport
| TermImport
;

TermImport:
  IMPORT package
;

package:
  package DOT package
| ID
;

/** class */
/** function or method */
/** variable */
// declaration
// assignment
qualifier:
  TermQualifier qualifier
| TermQualifier
;

TermQualifier:
  STATIC
| PRIVATE
;

define:
  TermDefine
| TermQualifier TermDefine
;

TermDefine:
  DEF ID
| DEF ID COLON type
;

assign:
  block
| ASSIGN block
| ASSIGN rightValue SEMI
;

/** flow control */
// # Note: the nested structure
// if elif else
// for while do-while
// match

/** right value */
rightValue:;

/** block */
block:
LBP
  multiLine 
RBP
;

multiLine:
  TermLine multiLine
| TermLine
;

TermLine:
  define
| define assign
| ID assign
| rightValue SEMI
| SEMI
;

/** Type system */
type:
  TYPE
| lambdaType
;

lambdaType:
  ARROW type
| LP RP ARROW type
| LP multiType RP ARROW types
;

multiType:
  type COMMA multiType
| type
;







if:
  IF LP rv RP block {}
| IF LP rv RP block else {}
;

else:
  ELSE block {}
| ELSE if
;

for: FOR LP vars COLON rv RP block;