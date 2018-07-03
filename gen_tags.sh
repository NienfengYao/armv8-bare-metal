find ./ -name "*.[chsS]" -print >> cscope.files
cscope -bkq -i cscope.files
ctags -R
