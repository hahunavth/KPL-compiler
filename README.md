# Compiler Construction

### Watch file:
```bash
while inotifywait -e close_write ../Test/test1.kpl ; do clear && ./parser ../Test/test1.kpl ; done
```

### Test example2
```bash
 while inotifywait -e close_write ../../2_parser/Test/example2.copy2.kpl ; do clear && ./parser ../../2_parser/Test/example2.copy2.kpl ; done
```

```bash
./script.sh ./2c_parser_completed/b/parser 2_parser/Test/example2.copy2.kpl
```