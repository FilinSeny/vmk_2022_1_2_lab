

section .data
    x dq 2.0
    c0 dq 0.5
    c1 dq 3.0
    c2 dq -1.5
    c3 dq 2.5
    c4 dq 9.5
    c5 dq 5.0
    c6 dq -5.0

section .text
global F1
global F2
global F3
global DF1
global DF2
global DF3

;3(0.5/(x+1) + 1)
F1:
    push ebp
    mov ebp, esp
    
    
    finit
    fld qword[ebp + 8];
    fld1
    faddp
    fstp qword[x]
    fld qword[c0]
    fld qword[x]
    fdivp
    ;fstp qword[x]
    ;fld qword[x]
    fld1
    faddp
    ;fstp qword[x]
    ;fld qword[x]
    fld qword[c1]
    fmulp
    ;fstp qword[x]
    ;fld qword[x]
    
    mov esp, ebp
    pop ebp
    ret
    
  
;-1.5(1/(x + 1)^2) 1 x 1 + x 1 + / 1.5 * 
DF1:
    push ebp,
    mov ebp, esp
    
    finit 
    fld1
    fld qword[ebp + 8]
    fld1
    faddp
    fstp qword[x]
    fld qword[x]
    fld qword[x]
    
    fmulp
    ;fst qword[x]
    fdivp
    ;fst qword[x]
    fld qword[c2]
    fmul
    
    mov esp, ebp
    pop ebp
    ret
    

;2.5*x - 9.5   
F2:
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[ebp + 8]
    fld qword[c3]
    fmulp
    fld qword[c4]
    fsubp
    
    mov esp, ebp
    pop ebp
    ret

DF2:
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[c3]
    
    mov esp, ebp
    pop ebp
    ret
    
    
;5/x

F3:
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[c5]
    fld qword[ebp + 8]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
    
DF3:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[c6]
    fld qword[ebp + 8]
    fld qword[ebp + 8]
    fmulp
    fdivp
    
    mov esp, ebp
    pop ebp
    ret    
         


