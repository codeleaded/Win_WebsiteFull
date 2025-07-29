from io import print

function FunctionButton1(r,e)
    if e.type==0
        io::print("[LL]:1 -> EVENT_NONE\n")
    elif e.type==1
        io::print("[LL]:1 -> EVENT_PRESSED\n")
    elif e.type==2
        io::print("[LL]:1 -> EVENT_INSIDE_RELEASED\n")
    elif e.type==3
        io::print("[LL]:1 -> EVENT_OUTSIDE_RELEASED\n")
    elif e.type==4
        io::print("[LL]:1 -> EVENT_DOWN\n")
    elif e.type==5
        io::print("[LL]:1 -> EVENT_INSIDE\n")
    elif e.type==6
        io::print("[LL]:1 -> EVENT_MOVED\n")
    elif e.type==7
        io::print("[LL]:1 -> EVENT_DRAGGED\n")
    elif e.type==8
        io::print("[LL]:1 -> EVENT_ENTERED\n")
    elif e.type==9
        io::print("[LL]:1 -> EVENT_EXITED\n")
    elif e.type==10
        io::print("[LL]:1 -> EVENT_EMTY\n")
    elif e.type==11
        io::print("[LL]:1 -> EVENT_FULL\n")
    elif e.type==12
        io::print("[LL]:1 -> EVENT_RESET\n")
    elif e.type==13
        io::print("[LL]:1 -> EVENT_START\n")
    elif e.type==14
        io::print("[LL]:1 -> EVENT_STOP\n")
    elif e.type==15
        io::print("[LL]:1 -> EVENT_FOCUSED\n")
    elif e.type==16
        io::print("[LL]:1 -> EVENT_UNFOCUSED\n")
    elif e.type==17
        io::print("[LL]:1 -> EVENT_ROTATE\n")
    end
    return
end

function FunctionButton2(r,e)
    if e.type==0
        io::print("[LL]:2 -> EVENT_NONE\n")
    elif e.type==1
        io::print("[LL]:2 -> EVENT_PRESSED\n")
    elif e.type==2
        io::print("[LL]:2 -> EVENT_INSIDE_RELEASED\n")
    elif e.type==3
        io::print("[LL]:2 -> EVENT_OUTSIDE_RELEASED\n")
    elif e.type==4
        io::print("[LL]:2 -> EVENT_DOWN\n")
    elif e.type==5
        io::print("[LL]:2 -> EVENT_INSIDE\n")
    elif e.type==6
        io::print("[LL]:2 -> EVENT_MOVED\n")
    elif e.type==7
        io::print("[LL]:2 -> EVENT_DRAGGED\n")
    elif e.type==8
        io::print("[LL]:2 -> EVENT_ENTERED\n")
    elif e.type==9
        io::print("[LL]:2 -> EVENT_EXITED\n")
    elif e.type==10
        io::print("[LL]:2 -> EVENT_EMTY\n")
    elif e.type==11
        io::print("[LL]:2 -> EVENT_FULL\n")
    elif e.type==12
        io::print("[LL]:2 -> EVENT_RESET\n")
    elif e.type==13
        io::print("[LL]:2 -> EVENT_START\n")
    elif e.type==14
        io::print("[LL]:2 -> EVENT_STOP\n")
    elif e.type==15
        io::print("[LL]:2 -> EVENT_FOCUSED\n")
    elif e.type==16
        io::print("[LL]:2 -> EVENT_UNFOCUSED\n")
    elif e.type==17
        io::print("[LL]:2 -> EVENT_ROTATE\n")
    end
    return
end


function main()

    dom::listen("button1",FunctionButton1)
    dom::listen("button2",FunctionButton2)

    return
end