.text
.global main
main:
  xor %rdi,%rdi
  call exit
  int3
.section .note.GNU-stack
