#include "/home/codeleaded/System/Static/Library/ComponentPack.h"
#include "/home/codeleaded/System/Static/Library/ComponentML.h"
#include "/home/codeleaded/System/Static/Library/ComponentDefines.h"
#include "/home/codeleaded/System/Static/Library/LuaLike.h"
#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"

Scene scene;
ComponentPack cg;
ComponentML cml;
LuaLike ll;

void Dom_EventHandler(void* r,EventId* e){
    Renderable* ra = (Renderable*)r;
    Component* c = Component_Scene_FindRR(&cg,ra);

    if(c){
        char* func = Component_Attr_is(c,"func") ? (char*)Component_Attr_Get(c,"func") : NULL;
        if(func){
            
            Variable ra = Variable_Make(
                "r","obj",
                (VariableMap[]){ VariableMap_Make((Variable[]){
                    Variable_Make("name","int",(Number[]){ 69 },sizeof(Number),0,NULL,NULL),
                    Variable_Null()
                })},
                sizeof(VariableMap),0,
                Scope_DestroyerOfType(&ll.ev.sc,"obj"),
                Scope_CpyerOfType(&ll.ev.sc,"obj")
            );
            Variable ev = Variable_Make(
                "e","obj",
                (VariableMap[]){ VariableMap_Make((Variable[]){
                    Variable_Make("type","int",(Number[]){ *e },sizeof(Number),0,NULL,NULL),
                    Variable_Null()
                })},
                sizeof(VariableMap),0,
                Scope_DestroyerOfType(&ll.ev.sc,"obj"),
                Scope_CpyerOfType(&ll.ev.sc,"obj")
            );
            
            
            //Variable ra = Variable_Null();
            //Variable ev = Variable_Make(
            //    "e","int",
            //    (Number[]){ *e },
            //    sizeof(Number),0,
            //    NULL,NULL
            //);

            Variable ret = LuaLike_Function(&ll,func,(Variable[]){ 
                ra,ev,VARIABLE_END
            });
            Variable_Free(&ret);
            Variable_Free(&ev);
            Variable_Free(&ra);

            //Scope_Print(&ll.ev.sc);
            //Component_Print(&cg);
            //Scene_Print(&scene);
        }
    }
}
Variable Dom_Listen(Enviroment* ev,CStr name,Variable* args){
    Variable* component = &args[0];
    Variable* func = &args[1];

    CStr funcname = *(CStr*)Variable_Data(func);
    Component* c = Component_Scene_FindNR(&cg,*(CStr*)Variable_Data(component));
    if(c) Component_Attr_Set(c,"func",funcname);

    return Variable_Null();
}

void Setup(AlxWindow* w){
    ll = LuaLike_New("./code/Main.ll","./bin");

    scene = Scene_New();

	cml = ComponentML_New(
        KeywordMap_Make((KeywordRP[]){
            KEYWORD_END
        }),
        OperatorMap_Make((OperatorRP[]){
            OperatorRP_Make((TT_Type[]){ TOKEN_EQUAL_SIGN,TOKEN_END },                          TOKEN_CUSTOM_ASS,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_PLUS_SIGN,TOKEN_END },                           TOKEN_CUSTOM_ADD,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_END },                          TOKEN_CUSTOM_SUB,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ASTERISK,TOKEN_END },                            TOKEN_CUSTOM_MUL,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_SLASH,TOKEN_END },                               TOKEN_CUSTOM_DIV,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,TOKEN_END },         TOKEN_CUSTOM_DEC,ARGS_IGNORE),
            
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_L,TOKEN_END },                    TOKEN_CUSTOM_TAGL,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_R,TOKEN_END },                    TOKEN_CUSTOM_TAGR,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_L,TOKEN_SLASH,TOKEN_END },        TOKEN_CUSTOM_TAGC,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_L,TOKEN_EXCLAMATION_MARK,
                                         TOKEN_END },                                           TOKEN_CUSTOM_TAGLEX0,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_L,TOKEN_EXCLAMATION_MARK,
                                         TOKEN_MINUS_SIGN,TOKEN_END },                          TOKEN_CUSTOM_TAGLEX1,ARGS_IGNORE),
    
            OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,TOKEN_END },         TOKEN_CUSTOM_LINECOMMENT,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_ANGLE_BRACKETS_L,TOKEN_EXCLAMATION_MARK,
                                         TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,TOKEN_END },         TOKEN_CUSTOM_BLOCKCOMMENTSTART,ARGS_IGNORE),
            OperatorRP_Make((TT_Type[]){ TOKEN_MINUS_SIGN,TOKEN_MINUS_SIGN,
                                         TOKEN_ANGLE_BRACKETS_R,TOKEN_END },                    TOKEN_CUSTOM_BLOCKCOMMENTEND,ARGS_IGNORE),
            OperatorRP_End()
        }),
        DirectiveMap_Make((Directive[]){
            Directive_Comment_Block(TOKEN_CUSTOM_BLOCKCOMMENTSTART,TOKEN_CUSTOM_BLOCKCOMMENTEND,True),
            Directive_Compress_Tag(TOKEN_CUSTOM_TAGOPEN,TOKEN_CUSTOM_TAGL,TOKEN_CUSTOM_TAGR),
            Directive_Compress_Tag(TOKEN_CUSTOM_TAGCLOSE,TOKEN_CUSTOM_TAGC,TOKEN_CUSTOM_TAGR),
            Directive_End()
        }),
        TT_TypeMap_Make((TT_Type[]){
            TOKEN_NEWLINE,
            TOKEN_END
        }),
        ReseterMap_Make((Reseter[]){ 
            // operators who might have two versions: 1 arg vs. 2 args are not listed: -
            { TOKEN_NONE,RESETER_NONE },
            { TOKEN_NUMBER,RESETER_ADD1 },
            { TOKEN_FLOAT,RESETER_ADD1 },
            { TOKEN_STRING,RESETER_ADD1 },
            
            { TOKEN_SPACE,RESETER_NONE },
            { TOKEN_NEWLINE,RESETER_NONE },// without semicolon like python
            { TOKEN_CARTURN,RESETER_NONE },
            { TOKEN_HTAB,RESETER_NONE },
            { TOKEN_VTAB,RESETER_NONE },
    
            { TOKEN_COMMA,RESETER_RST },

            { TOKEN_PARENTHESES_R,RESETER_TO1 },
            { TOKEN_SQUARE_BRACKETS_R,RESETER_NONE },
            { TOKEN_CURLY_BRACES_R,RESETER_NONE },
            //{ TOKEN_ANGLE_BRACKETS_R,RESETER_NONE }, //also < and > operator
            { TOKEN_DOUBLE_ANGLE_BRACKETS_R,RESETER_NONE },
            { TOKEN_WHITE_SQUARE_BRACKETS_R,RESETER_NONE },
            
            { TOKEN_PARENTHESES_L,RESETER_RST },
            { TOKEN_SQUARE_BRACKETS_L,RESETER_RST },
            { TOKEN_CURLY_BRACES_L,RESETER_RST },
            //{ TOKEN_ANGLE_BRACKETS_L,RESETER_RST }, //also < and > operator
            { TOKEN_DOUBLE_ANGLE_BRACKETS_L,RESETER_RST },
            { TOKEN_WHITE_SQUARE_BRACKETS_L,RESETER_RST },
            { TOKEN_SEMICOLON,RESETER_RST },
            { TOKEN_COLON,RESETER_RST },
            { TOKEN_EXCLAMATION_MARK,RESETER_RST },
            { TOKEN_QUESTION_MARK,RESETER_RST },
            { TOKEN_ELLIPSIS,RESETER_RST },
            { TOKEN_PLUS_SIGN,RESETER_RST },
            { TOKEN_MULTIPLICATION_SIGN,RESETER_RST },
            { TOKEN_DIVISION_SIGN,RESETER_RST },
            { TOKEN_EQUAL_SIGN,RESETER_RST },
            { TOKEN_NOT_EQUAL_SIGN,RESETER_RST },
            { TOKEN_LESS_THAN,RESETER_RST },
            { TOKEN_GREATER_THAN,RESETER_RST },
            { TOKEN_LESS_THAN_OR_EQUAL_TO,RESETER_RST },
            { TOKEN_GREATER_THAN_OR_EQUAL_TO,RESETER_RST },
            { TOKEN_APPROXIMATION_SIGN,RESETER_RST },
            { TOKEN_PLUS_MINUS_SIGN,RESETER_RST },
            { TOKEN_AMPERSAND,RESETER_RST },
            { TOKEN_AT_SIGN,RESETER_RST },
            { TOKEN_ASTERISK,RESETER_RST },
            { TOKEN_CARET,RESETER_RST },
            { TOKEN_TILDE,RESETER_RST },
            { TOKEN_SLASH,RESETER_RST },
            { TOKEN_BACKSLASH,RESETER_RST },
            { TOKEN_UNDERSCORE,RESETER_RST },
            { TOKEN_PIPE,RESETER_RST },
            { TOKEN_PERCENT,RESETER_RST },
            { TOKEN_HASH_POUND_SIGN,RESETER_RST },
            { TOKEN_SINGLE_QUOTE,RESETER_RST },
            { TOKEN_DOUBLE_QUOTE,RESETER_RST },
            { TOKEN_BACKTICK,RESETER_RST },
            { TOKEN_PRIME,RESETER_RST },
            { TOKEN_DOUBLE_PRIME,RESETER_RST },
            { TOKEN_SECTION_SYMBOL,RESETER_RST },
            { TOKEN_DEGREE_SYMBOL,RESETER_RST },
            { TOKEN_FRACTION_SLASH,RESETER_RST },
            { TOKEN_INTERROBANG,RESETER_RST },
            { TOKEN_BULLET_POINT,RESETER_RST },
    
            { TOKEN_CAST,RESETER_ADD1 },
            { TOKEN_FUNCTION,RESETER_ADD1 },
            { TOKEN_CONSTSTRING_SINGLE,RESETER_ADD1 },
            { TOKEN_CONSTSTRING_DOUBLE,RESETER_ADD1 },

            { TOKEN_END,RESETER_RST }
        })
    );
    
    ComponentML_Source(&cml,"./code/Main.alxml");
    //TokenMap_Print(&cml.tm);

    cg = ComponentML_Build(&cml);
    Component_Scene_Push_R(&cg,&scene);
    Component_Scene_Event_R(&cg,&scene,Dom_EventHandler);

    LuaLike_CreateFunc_Std(&ll,"C","dom::listen",NULL,(Member[]){
        Member_New("str","component"),
        Member_New(NULL,"fn"),
        MEMBER_END
    },(void*)Dom_Listen);
    
    Variable ret = LuaLike_Function(&ll,"main",(Variable[]){ 
        VARIABLE_END
    });
    LuaLike_PrintVariable(&ll,&ret);
    Variable_Free(&ret);
}
void Update(AlxWindow* w){
    Scene_Update(&scene,window.Strokes,GetMouse(),GetMouseBefore());

	Clear(BLACK);

	Scene_Render(WINDOW_STD_ARGS,&scene);
}
void Delete(AlxWindow* w){
    LuaLike_Free(&ll);
	Scene_Free(&scene);
    Component_Free(&cg);
    ComponentML_Free(&cml);
}

int main(){
    if(Create("Website Full",1920,1080,1,1,Setup,Update,Delete))
        Start();
    return 0;
}