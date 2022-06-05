### Test
```bash
while inotifywait -e close_write ../*.c ; do clear && make && ./3.1_symtab; done
```