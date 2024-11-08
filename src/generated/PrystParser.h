
// Generated from PrystParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PrystParser : public antlr4::Parser {
public:
  enum {
    PRINT = 1, CLASS = 2, EXTENDS = 3, ELSE = 4, FALSE = 5, FOR = 6, IF = 7, 
    NULL_ = 8, RETURN = 9, SUPER = 10, THIS = 11, TRUE = 12, WHILE = 13, 
    NEW = 14, CONVERT = 15, NAMESPACE = 16, MODULE = 17, IMPORT = 18, USING = 19, 
    LET = 20, FN = 21, CONST = 22, CONST_EXPR = 23, TRY = 24, CATCH = 25, 
    INT = 26, FLOAT = 27, BOOL = 28, STR = 29, VOID = 30, LPAREN = 31, RPAREN = 32, 
    LBRACE = 33, RBRACE = 34, LBRACKET = 35, RBRACKET = 36, COMMA = 37, 
    DOT = 38, MINUS = 39, PLUS = 40, SEMICOLON = 41, SLASH = 42, STAR = 43, 
    BANG = 44, EQUAL = 45, GREATER = 46, LESS = 47, NOT_EQUAL = 48, EQUAL_EQUAL = 49, 
    GREATER_EQUAL = 50, LESS_EQUAL = 51, AND = 52, OR = 53, INCREMENT = 54, 
    DECREMENT = 55, PERCENT = 56, ARROW = 57, DOUBLE_COLON = 58, NUMBER = 59, 
    IDENTIFIER = 60, STRING_START = 61, COMMENT = 62, WS = 63, STRING_CONTENT = 64, 
    ESCAPE_SEQ = 65, INTERP_START = 66, STRING_END = 67
  };

  enum {
    RuleProgram = 0, RuleDeclaration = 1, RuleUsingDecl = 2, RuleNamespaceDecl = 3, 
    RuleModuleDecl = 4, RuleImportDecl = 5, RuleImportPath = 6, RuleFunctionDecl = 7, 
    RuleNamedFunction = 8, RuleLambdaFunction = 9, RuleFunctionBody = 10, 
    RuleVariableDecl = 11, RuleClassDeclaration = 12, RuleClassBody = 13, 
    RuleClassMember = 14, RuleParamList = 15, RuleParam = 16, RuleParamTypeList = 17, 
    RuleType = 18, RuleStatement = 19, RuleTryStmtWrapper = 20, RuleCatchBlock = 21, 
    RuleExpression = 22, RuleStringLiteralRule = 23, RuleStringPart = 24, 
    RuleAssignment = 25, RuleLogicOr = 26, RuleLogicAnd = 27, RuleEquality = 28, 
    RuleComparison = 29, RuleAddition = 30, RuleMultiplication = 31, RuleUnary = 32, 
    RulePostfix = 33, RuleSuffix = 34, RuleCallSuffix = 35, RuleMemberSuffix = 36, 
    RuleCall = 37, RulePrimary = 38, RuleQualifiedIdentifier = 39, RuleNewExpression = 40, 
    RuleArguments = 41, RuleTypeCastExpr = 42, RuleTypeConversionExpr = 43, 
    RuleClassConversionExpr = 44
  };

  explicit PrystParser(antlr4::TokenStream *input);

  PrystParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~PrystParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class DeclarationContext;
  class UsingDeclContext;
  class NamespaceDeclContext;
  class ModuleDeclContext;
  class ImportDeclContext;
  class ImportPathContext;
  class FunctionDeclContext;
  class NamedFunctionContext;
  class LambdaFunctionContext;
  class FunctionBodyContext;
  class VariableDeclContext;
  class ClassDeclarationContext;
  class ClassBodyContext;
  class ClassMemberContext;
  class ParamListContext;
  class ParamContext;
  class ParamTypeListContext;
  class TypeContext;
  class StatementContext;
  class TryStmtWrapperContext;
  class CatchBlockContext;
  class ExpressionContext;
  class StringLiteralRuleContext;
  class StringPartContext;
  class AssignmentContext;
  class LogicOrContext;
  class LogicAndContext;
  class EqualityContext;
  class ComparisonContext;
  class AdditionContext;
  class MultiplicationContext;
  class UnaryContext;
  class PostfixContext;
  class SuffixContext;
  class CallSuffixContext;
  class MemberSuffixContext;
  class CallContext;
  class PrimaryContext;
  class QualifiedIdentifierContext;
  class NewExpressionContext;
  class ArgumentsContext;
  class TypeCastExprContext;
  class TypeConversionExprContext;
  class ClassConversionExprContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<NamespaceDeclContext *> namespaceDecl();
    NamespaceDeclContext* namespaceDecl(size_t i);
    std::vector<ModuleDeclContext *> moduleDecl();
    ModuleDeclContext* moduleDecl(size_t i);
    std::vector<ImportDeclContext *> importDecl();
    ImportDeclContext* importDecl(size_t i);
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDeclContext *functionDecl();
    VariableDeclContext *variableDecl();
    ClassDeclarationContext *classDeclaration();
    UsingDeclContext *usingDecl();
    StatementContext *statement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  UsingDeclContext : public antlr4::ParserRuleContext {
  public:
    UsingDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UsingDeclContext() = default;
    void copyFrom(UsingDeclContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  GlobalUsingDeclContext : public UsingDeclContext {
  public:
    GlobalUsingDeclContext(UsingDeclContext *ctx);

    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *USING();
    antlr4::tree::TerminalNode *NAMESPACE();
    antlr4::tree::TerminalNode *MODULE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockScopedModuleDeclContext : public UsingDeclContext {
  public:
    BlockScopedModuleDeclContext(UsingDeclContext *ctx);

    antlr4::tree::TerminalNode *USING();
    antlr4::tree::TerminalNode *MODULE();
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockScopedNamespaceDeclContext : public UsingDeclContext {
  public:
    BlockScopedNamespaceDeclContext(UsingDeclContext *ctx);

    antlr4::tree::TerminalNode *USING();
    antlr4::tree::TerminalNode *NAMESPACE();
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UsingDeclContext* usingDecl();

  class  NamespaceDeclContext : public antlr4::ParserRuleContext {
  public:
    NamespaceDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMESPACE();
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<ModuleDeclContext *> moduleDecl();
    ModuleDeclContext* moduleDecl(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceDeclContext* namespaceDecl();

  class  ModuleDeclContext : public antlr4::ParserRuleContext {
  public:
    ModuleDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MODULE();
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModuleDeclContext* moduleDecl();

  class  ImportDeclContext : public antlr4::ParserRuleContext {
  public:
    ImportDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    ImportPathContext *importPath();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportDeclContext* importDecl();

  class  ImportPathContext : public antlr4::ParserRuleContext {
  public:
    ImportPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOUBLE_COLON();
    antlr4::tree::TerminalNode* DOUBLE_COLON(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportPathContext* importPath();

  class  FunctionDeclContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamedFunctionContext *namedFunction();
    LambdaFunctionContext *lambdaFunction();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclContext* functionDecl();

  class  NamedFunctionContext : public antlr4::ParserRuleContext {
  public:
    NamedFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FN();
    antlr4::tree::TerminalNode *LESS();
    TypeContext *type();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    FunctionBodyContext *functionBody();
    ParamListContext *paramList();
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *VOID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamedFunctionContext* namedFunction();

  class  LambdaFunctionContext : public antlr4::ParserRuleContext {
  public:
    LambdaFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    ParamListContext *paramList();
    TypeContext *type();
    antlr4::tree::TerminalNode *VOID();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LambdaFunctionContext* lambdaFunction();

  class  FunctionBodyContext : public antlr4::ParserRuleContext {
  public:
    FunctionBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionBodyContext* functionBody();

  class  VariableDeclContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VariableDeclContext() = default;
    void copyFrom(VariableDeclContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TypedConstVariableDeclContext : public VariableDeclContext {
  public:
    TypedConstVariableDeclContext(VariableDeclContext *ctx);

    antlr4::tree::TerminalNode *CONST();
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypedVariableDeclContext : public VariableDeclContext {
  public:
    TypedVariableDeclContext(VariableDeclContext *ctx);

    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InferredVariableDeclContext : public VariableDeclContext {
  public:
    InferredVariableDeclContext(VariableDeclContext *ctx);

    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InferredConstVariableDeclContext : public VariableDeclContext {
  public:
    InferredConstVariableDeclContext(VariableDeclContext *ctx);

    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstExprVariableDeclContext : public VariableDeclContext {
  public:
    ConstExprVariableDeclContext(VariableDeclContext *ctx);

    antlr4::tree::TerminalNode *CONST_EXPR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UninitializedVariableDeclContext : public VariableDeclContext {
  public:
    UninitializedVariableDeclContext(VariableDeclContext *ctx);

    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VariableDeclContext* variableDecl();

  class  ClassDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ClassDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLASS();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    ClassBodyContext *classBody();
    antlr4::tree::TerminalNode *EXTENDS();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDeclarationContext* classDeclaration();

  class  ClassBodyContext : public antlr4::ParserRuleContext {
  public:
    ClassBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ClassMemberContext *> classMember();
    ClassMemberContext* classMember(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassBodyContext* classBody();

  class  ClassMemberContext : public antlr4::ParserRuleContext {
  public:
    ClassMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ClassMemberContext() = default;
    void copyFrom(ClassMemberContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ClassMemberConstTypedDeclContext : public ClassMemberContext {
  public:
    ClassMemberConstTypedDeclContext(ClassMemberContext *ctx);

    antlr4::tree::TerminalNode *CONST();
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassMemberConstInferredDeclContext : public ClassMemberContext {
  public:
    ClassMemberConstInferredDeclContext(ClassMemberContext *ctx);

    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassMemberInferredDeclContext : public ClassMemberContext {
  public:
    ClassMemberInferredDeclContext(ClassMemberContext *ctx);

    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassMemberFunctionDeclContext : public ClassMemberContext {
  public:
    ClassMemberFunctionDeclContext(ClassMemberContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *ARROW();
    TypeContext *type();
    FunctionBodyContext *functionBody();
    ParamListContext *paramList();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ClassMemberDeclContext : public ClassMemberContext {
  public:
    ClassMemberDeclContext(ClassMemberContext *ctx);

    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ClassMemberContext* classMember();

  class  ParamListContext : public antlr4::ParserRuleContext {
  public:
    ParamListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParamContext *> param();
    ParamContext* param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamListContext* paramList();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *FN();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ParamTypeListContext *paramTypeList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamContext* param();

  class  ParamTypeListContext : public antlr4::ParserRuleContext {
  public:
    ParamTypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamTypeListContext* paramTypeList();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeContext() = default;
    void copyFrom(TypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FloatTypeContext : public TypeContext {
  public:
    FloatTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *FLOAT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LambdaTypeContext : public TypeContext {
  public:
    LambdaTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *ARROW();
    TypeContext *type();
    antlr4::tree::TerminalNode *VOID();
    ParamTypeListContext *paramTypeList();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayTypeContext : public TypeContext {
  public:
    ArrayTypeContext(TypeContext *ctx);

    TypeContext *type();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StrTypeContext : public TypeContext {
  public:
    StrTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *STR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IntTypeContext : public TypeContext {
  public:
    IntTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *INT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VoidTypeContext : public TypeContext {
  public:
    VoidTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *VOID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierTypeContext : public TypeContext {
  public:
    IdentifierTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionTypeContext : public TypeContext {
  public:
    FunctionTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *FN();
    antlr4::tree::TerminalNode *LESS();
    TypeContext *type();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ParamTypeListContext *paramTypeList();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolTypeContext : public TypeContext {
  public:
    BoolTypeContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *BOOL();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeContext* type();
  TypeContext* type(int precedence);
  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  WhileStatementContext : public StatementContext {
  public:
    WhileStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PrintStatementContext : public StatementContext {
  public:
    PrintStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *PRINT();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStatementContext : public StatementContext {
  public:
    BlockStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprStatementContext : public StatementContext {
  public:
    ExprStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TryStmtContext : public StatementContext {
  public:
    TryStmtContext(StatementContext *ctx);

    TryStmtWrapperContext *tryStmtWrapper();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForStatementContext : public StatementContext {
  public:
    ForStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();
    VariableDeclContext *variableDecl();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStatementContext : public StatementContext {
  public:
    IfStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnStatementContext : public StatementContext {
  public:
    ReturnStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  TryStmtWrapperContext : public antlr4::ParserRuleContext {
  public:
    TryStmtWrapperContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TryStmtWrapperContext() = default;
    void copyFrom(TryStmtWrapperContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TryStatementContext : public TryStmtWrapperContext {
  public:
    TryStatementContext(TryStmtWrapperContext *ctx);

    antlr4::tree::TerminalNode *TRY();
    StatementContext *statement();
    std::vector<CatchBlockContext *> catchBlock();
    CatchBlockContext* catchBlock(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TryStmtWrapperContext* tryStmtWrapper();

  class  CatchBlockContext : public antlr4::ParserRuleContext {
  public:
    CatchBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CatchBlockContext() = default;
    void copyFrom(CatchBlockContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CatchStatementContext : public CatchBlockContext {
  public:
    CatchStatementContext(CatchBlockContext *ctx);

    antlr4::tree::TerminalNode *CATCH();
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CatchBlockContext* catchBlock();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignmentContext *assignment();
    LambdaFunctionContext *lambdaFunction();
    TypeCastExprContext *typeCastExpr();
    TypeConversionExprContext *typeConversionExpr();
    ClassConversionExprContext *classConversionExpr();
    StringLiteralRuleContext *stringLiteralRule();
    LogicOrContext *logicOr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  StringLiteralRuleContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StringLiteralRuleContext() = default;
    void copyFrom(StringLiteralRuleContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  StringLiteralExprContext : public StringLiteralRuleContext {
  public:
    StringLiteralExprContext(StringLiteralRuleContext *ctx);

    antlr4::tree::TerminalNode *STRING_START();
    antlr4::tree::TerminalNode *STRING_END();
    std::vector<StringPartContext *> stringPart();
    StringPartContext* stringPart(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StringLiteralRuleContext* stringLiteralRule();

  class  StringPartContext : public antlr4::ParserRuleContext {
  public:
    StringPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_CONTENT();
    antlr4::tree::TerminalNode *ESCAPE_SEQ();
    antlr4::tree::TerminalNode *INTERP_START();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringPartContext* stringPart();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();
    CallContext *call();
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  LogicOrContext : public antlr4::ParserRuleContext {
  public:
    LogicOrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicAndContext *> logicAnd();
    LogicAndContext* logicAnd(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicOrContext* logicOr();

  class  LogicAndContext : public antlr4::ParserRuleContext {
  public:
    LogicAndContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityContext *> equality();
    EqualityContext* equality(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicAndContext* logicAnd();

  class  EqualityContext : public antlr4::ParserRuleContext {
  public:
    EqualityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ComparisonContext *> comparison();
    ComparisonContext* comparison(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NOT_EQUAL();
    antlr4::tree::TerminalNode* NOT_EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUAL_EQUAL();
    antlr4::tree::TerminalNode* EQUAL_EQUAL(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityContext* equality();

  class  ComparisonContext : public antlr4::ParserRuleContext {
  public:
    ComparisonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditionContext *> addition();
    AdditionContext* addition(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS();
    antlr4::tree::TerminalNode* LESS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS_EQUAL();
    antlr4::tree::TerminalNode* LESS_EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER_EQUAL();
    antlr4::tree::TerminalNode* GREATER_EQUAL(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonContext* comparison();

  class  AdditionContext : public antlr4::ParserRuleContext {
  public:
    AdditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicationContext *> multiplication();
    MultiplicationContext* multiplication(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditionContext* addition();

  class  MultiplicationContext : public antlr4::ParserRuleContext {
  public:
    MultiplicationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryContext *> unary();
    UnaryContext* unary(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STAR();
    antlr4::tree::TerminalNode* STAR(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SLASH();
    antlr4::tree::TerminalNode* SLASH(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PERCENT();
    antlr4::tree::TerminalNode* PERCENT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicationContext* multiplication();

  class  UnaryContext : public antlr4::ParserRuleContext {
  public:
    UnaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryContext *unary();
    antlr4::tree::TerminalNode *BANG();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *INCREMENT();
    antlr4::tree::TerminalNode *DECREMENT();
    PostfixContext *postfix();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryContext* unary();

  class  PostfixContext : public antlr4::ParserRuleContext {
  public:
    PostfixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryContext *primary();
    std::vector<SuffixContext *> suffix();
    SuffixContext* suffix(size_t i);
    std::vector<antlr4::tree::TerminalNode *> INCREMENT();
    antlr4::tree::TerminalNode* INCREMENT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DECREMENT();
    antlr4::tree::TerminalNode* DECREMENT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PostfixContext* postfix();

  class  SuffixContext : public antlr4::ParserRuleContext {
  public:
    SuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CallSuffixContext *callSuffix();
    MemberSuffixContext *memberSuffix();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SuffixContext* suffix();

  class  CallSuffixContext : public antlr4::ParserRuleContext {
  public:
    CallSuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentsContext *arguments();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallSuffixContext* callSuffix();

  class  MemberSuffixContext : public antlr4::ParserRuleContext {
  public:
    MemberSuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentsContext *arguments();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MemberSuffixContext* memberSuffix();

  class  CallContext : public antlr4::ParserRuleContext {
  public:
    CallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdentifierContext *qualifiedIdentifier();
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallContext* call();

  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *NUMBER();
    QualifiedIdentifierContext *qualifiedIdentifier();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentsContext *arguments();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SUPER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    NewExpressionContext *newExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryContext* primary();

  class  QualifiedIdentifierContext : public antlr4::ParserRuleContext {
  public:
    QualifiedIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOUBLE_COLON();
    antlr4::tree::TerminalNode* DOUBLE_COLON(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedIdentifierContext* qualifiedIdentifier();

  class  NewExpressionContext : public antlr4::ParserRuleContext {
  public:
    NewExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEW();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentsContext *arguments();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NewExpressionContext* newExpression();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  TypeCastExprContext : public antlr4::ParserRuleContext {
  public:
    TypeCastExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeCastExprContext* typeCastExpr();

  class  TypeConversionExprContext : public antlr4::ParserRuleContext {
  public:
    TypeConversionExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *CONVERT();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeConversionExprContext* typeConversionExpr();

  class  ClassConversionExprContext : public antlr4::ParserRuleContext {
  public:
    ClassConversionExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *CONVERT();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassConversionExprContext* classConversionExpr();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool typeSempred(TypeContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

