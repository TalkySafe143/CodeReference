@echo off

rem Las soluciones ya deben estar compilados.
rem El primer parametro es la solución normal
rem El segundo parametro es la solución lenta
rem El tercer parametro es el generador
rem El Cuarto parametro es el numero de casos a probar.

if [%4]==[] (set /A numLoop = 100) else (set /A numLoop = %4)

set "diff_found="

for /l %%x in (1, 1, %numLoop%) do (
    echo %%x
    %3 > input.in
    %1 < input.in > output.out 
    %2 < input.in > output2.out

    fc output.out output2.out > diagnostics
    if errorlevel 1 (
        set "diff_found=y"
        goto :break
    )
)

:break

if defined diff_found (
    echo A difference has been found.
    echo Input: 
    type input.in
    echo.
    echo.

    echo Output:
    type output.out
    echo.

    echo Expected:
    type output2.out
    echo.
) else (
    echo All tests passed :D
)

del input.in
del output.out
del output2.out
