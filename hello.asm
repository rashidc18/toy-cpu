jmp $start

$putc
  syscall %OUT_CHAR
  ret

$putlnc
  cal $putc
  psi '\n'
  cal $putc
  ret

$start
  psi 'H'
  cal $putc
  psi 'e'
  cal $putc
  psi 'l'
  cal $putc
  psi 'l'
  cal $putc
  psi 'o'
  cal $putc
  psi '!'
  cal $putlnc
  hlt
