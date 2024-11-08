    // Overrides for visiting different AST nodes
    antlrcpp::Any visitProgram(PrystParser::ProgramContext* ctx) override;
    antlrcpp::Any visitDeclaration(PrystParser::DeclarationContext* ctx) override;
    antlrcpp::Any visitNamedFunction(PrystParser::NamedFunctionContext* ctx) override;
    antlrcpp::Any visitAnonymousFunction(PrystParser::AnonymousFunctionContext* ctx) override;
    antlrcpp::Any visitTypedAnonymousFunction(PrystParser::TypedAnonymousFunctionContext* ctx) override;
    antlrcpp::Any visitVariableDecl(PrystParser::VariableDeclContext* ctx) override;
    antlrcpp::Any visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) override;
    antlrcpp::Any visitClassBody(PrystParser::ClassBodyContext* ctx) override;
    antlrcpp::Any visitClassVariableDecl(PrystParser::ClassVariableDeclContext* ctx) override;
    antlrcpp::Any visitClassFunctionDecl(PrystParser::ClassFunctionDeclContext* ctx) override;
    antlrcpp::Any visitParamList(PrystParser::ParamListContext* ctx) override;
    antlrcpp::Any visitSimpleParam(PrystParser::SimpleParamContext* ctx) override;
    antlrcpp::Any visitFunctionParam(PrystParser::FunctionParamContext* ctx) override;
    antlrcpp::Any visitBasicType(PrystParser::BasicTypeContext* ctx) override;
    antlrcpp::Any visitArrayType(PrystParser::ArrayTypeContext* ctx) override;
    antlrcpp::Any visitFunctionType(PrystParser::FunctionTypeContext* ctx) override;
    antlrcpp::Any visitClassType(PrystParser::ClassTypeContext* ctx) override;
    antlrcpp::Any visitTypeList(PrystParser::TypeListContext* ctx) override;
    antlrcpp::Any visitExprStatement(PrystParser::ExprStatementContext* ctx) override;
    antlrcpp::Any visitIfStatement(PrystParser::IfStatementContext* ctx) override;
    antlrcpp::Any visitWhileStatement(PrystParser::WhileStatementContext* ctx) override;
    antlrcpp::Any visitForStatement(PrystParser::ForStatementContext* ctx) override;
    antlrcpp::Any visitReturnStatement(PrystParser::ReturnStatementContext* ctx) override;
    antlrcpp::Any visitBlockStatement(PrystParser::BlockStatementContext* ctx) override;
    antlrcpp::Any visitExpression(PrystParser::ExpressionContext* ctx) override;
    antlrcpp::Any visitAssignment(PrystParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitLogicOr(PrystParser::LogicOrContext* ctx) override;
    antlrcpp::Any visitLogicAnd(PrystParser::LogicAndContext* ctx) override;
    antlrcpp::Any visitEquality(PrystParser::EqualityContext* ctx) override;
    antlrcpp::Any visitComparison(PrystParser::ComparisonContext* ctx) override;
    antlrcpp::Any visitAddition(PrystParser::AdditionContext* ctx) override;
    antlrcpp::Any visitMultiplication(PrystParser::MultiplicationContext* ctx) override;
    antlrcpp::Any visitUnary(PrystParser::UnaryContext* ctx) override;
    antlrcpp::Any visitPostfix(PrystParser::PostfixContext* ctx) override;
    antlrcpp::Any visitCall(PrystParser::CallContext* ctx) override;
    antlrcpp::Any visitLiteralExpr(PrystParser::LiteralExprContext* ctx) override;
    antlrcpp::Any visitThisExpr(PrystParser::ThisExprContext* ctx) override;
    antlrcpp::Any visitNumberExpr(PrystParser::NumberExprContext* ctx) override;
    antlrcpp::Any visitStringExpr(PrystParser::StringExprContext* ctx) override;
    antlrcpp::Any visitIdentifierExpr(PrystParser::IdentifierExprContext* ctx) override;
    antlrcpp::Any visitGroupExpr(PrystParser::GroupExprContext* ctx) override;
    antlrcpp::Any visitTypeCastExpr(PrystParser::TypeCastExprContext* ctx) override;
    antlrcpp::Any visitTypeConversionExpr(PrystParser::TypeConversionExprContext* ctx) override;
    antlrcpp::Any visitSuperExpr(PrystParser::SuperExprContext* ctx) override;
    antlrcpp::Any visitNewExpr(PrystParser::NewExprContext* ctx) override;
    antlrcpp::Any visitAnonymousFunctionExpr(PrystParser::AnonymousFunctionExprContext* ctx) override;
    antlrcpp::Any visitClassConversionExpr(PrystParser::ClassConversionExprContext* ctx) override;
    antlrcpp::Any visitNewExpression(PrystParser::NewExpressionContext* ctx) override;
    antlrcpp::Any visitArguments(PrystParser::ArgumentsContext* ctx) override;