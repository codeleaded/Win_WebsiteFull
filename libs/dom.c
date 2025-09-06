#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"
#include "/home/codeleaded/System/Static/Library/Dom.h"


Dom* d = NULL;

void Dom_EventHandler(void* r,EventId* e){
    if(d){
        Renderable* ra = (Renderable*)r;
        Component* c = Component_Scene_FindRR(&d->cg,ra);

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
                    Scope_DestroyerOfType(&d->ll.ev.sc,"obj"),
                    Scope_CpyerOfType(&d->ll.ev.sc,"obj")
                );
                Variable ev = Variable_Make(
                    "e","obj",
                    (VariableMap[]){ VariableMap_Make((Variable[]){
                        Variable_Make("type","int",(Number[]){ *e },sizeof(Number),0,NULL,NULL),
                        Variable_Null()
                    })},
                    sizeof(VariableMap),0,
                    Scope_DestroyerOfType(&d->ll.ev.sc,"obj"),
                    Scope_CpyerOfType(&d->ll.ev.sc,"obj")
                );

                Variable ret = LuaLike_Function(&d->ll,func,(Variable[]){ 
                    ra,ev,VARIABLE_END
                });
                Variable_Free(&ret);
                Variable_Free(&ev);
                Variable_Free(&ra);
            }
        }
    }
}

Variable Dom_New(Enviroment* ev,CStr name,Variable* args){
    Variable ret = Variable_Make(
        "OBJECT","obj",
        (VariableMap[]){ VariableMap_New() },
        sizeof(VariableMap),ev->sc.range-1,
        Scope_DestroyerOfType(&ev->sc,"obj"),
        Scope_CpyerOfType(&ev->sc,"obj")
    );
    return ret;
}
Variable Dom_Listen(Enviroment* ev,CStr name,Variable* args){
    Variable* component = &args[0];
    Variable* func = &args[1];

    CStr funcname = *(CStr*)Variable_Data(func);
    Component* c = Component_Scene_FindNR(&d->cg,*(CStr*)Variable_Data(component));
    if(c) Component_Attr_Set(c,"func",funcname);

    return Variable_Null();
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    ExternFunctionMap_PushContained_C(Extern_Functions,funcs,(ExternFunction[]){
        ExternFunction_New("listen",NULL,(Member[]){
            Member_New("str","component"),
            Member_New(NULL,"fn"),
            MEMBER_END
        },(void*)Dom_Listen),
        ExternFunction_Null()
    });
}
