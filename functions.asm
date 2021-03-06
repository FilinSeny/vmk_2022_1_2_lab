

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
global f1
global f2
global f3
global df1
global df2
global df3

;3(0.5/(x+1) + 1)
f1:
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
   
   
    fld1
    faddp
   
   
    fld qword[c1]
    fmulp
   
   
    
    mov esp, ebp
    pop ebp
    ret
    
  
;-1.5(1/(x + 1)^2) 1 x 1 + x 1 + / 1.5 * 
df1:
    push ebp,
    mov ebp, esp
    
    finit 
    fld1
    fld qword[ebp + 8]
    fld1
    faddp
	fstp qword[ebp + 8]
	
    fld qword[ebp+8]
	fld qword[ebp+8]
    fmulp   
    fdivp
    fld qword[c2]
    fmul
    
    mov esp, ebp
    pop ebp
    ret
    

;2.5*x - 9.5   
f2:
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

df2:
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[c3]
    
    mov esp, ebp
    pop ebp
    ret
    
    
;5/x

f3:
    push ebp
    mov ebp, esp
    
    finit 
    fld qword[c5]
    fld qword[ebp + 8]
    fdivp
    
    mov esp, ebp
    pop ebp
    ret
    
    
df3:
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
         


