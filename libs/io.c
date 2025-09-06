#include "/home/codeleaded/System/Static/Library/AlxCallStack.h"
#include "/home/codeleaded/System/Static/Library/AlxExternFunctions.h"
#include "/home/codeleaded/System/Static/Library/LuaLikeDefines.h"

Variable io_input(Enviroment* ev,CStr name,Variable* args){
    Variable* a = &args[0];
    
    char buffer[1024];
    char* back = fgets(buffer,1024,stdin);
    Variable ret = Variable_Make(
        "INPUT","str",(CStr[]){ CStr_Cpy(buffer) },
        sizeof(CStr),ev->sc.range-1,
        Scope_DestroyerOfType(&ev->sc,"str"),
        Scope_CpyerOfType(&ev->sc,"str")
    );
    return ret;
}
Variable io_print(Enviroment* ev,CStr name,Variable* args){
    Variable* a = &args[0];
    
    printf("%s",*(CStr*)a->data);
    Variable ret = Variable_Null();
    return ret;
}
Variable io_error(Enviroment* ev,CStr name,Variable* args){
    Variable* a = &args[0];
    
    printf("\033[31m%s\033[37m",*(CStr*)a->data);
    Variable ret = Variable_Null();
    return ret;
}

void Ex_Packer(ExternFunctionMap* Extern_Functions,Vector* funcs,Scope* s){//Vector<CStr>
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("input",NULL,(Member[]){ 
        MEMBER_END 
    },(void*)io_input));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("print",NULL,(Member[]){ 
        Member_New(NULL,"s"),
        MEMBER_END
    },(void*)io_print));
    ExternFunctionMap_PushContained(Extern_Functions,funcs,ExternFunction_New("error",NULL,(Member[]){ 
        Member_New(NULL,"s"),
        MEMBER_END
    },(void*)io_error));
}
