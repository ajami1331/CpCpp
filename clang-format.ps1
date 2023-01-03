Get-ChildItem -Include *.cpp,*.h,*.h.in -File -Recurse -ErrorAction SilentlyContinue | select Fullname | ForEach-Object -Process {clang-format -i --style=file --verbose $_.fullname}