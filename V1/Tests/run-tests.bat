@echo off

echo ========================================
echo       InfiniteScript V1 Test Suite
echo ========================================
echo.

echo [1/4] Core runtime
Inf.exe run V1\Tests\CoreRuntime.infs

if errorlevel 1 (
    echo.
    echo FAILED: Core runtime
    exit /b 1
)

echo.
echo [2/4] Existing runtime tests
Inf.exe run Examples\RuntimeSuite.infs

if errorlevel 1 (
    echo.
    echo FAILED: RuntimeSuite
    exit /b 1
)

echo.
echo [3/4] Conditional tests
Inf.exe run Examples\IfTest.infs

if errorlevel 1 (
    echo.
    echo FAILED: IfTest
    exit /b 1
)

echo.
echo [4/4] Function tests
Inf.exe run Examples\FunctionTest.infs

if errorlevel 1 (
    echo.
    echo FAILED: Function tests
    exit /b 1
)

echo.
echo ========================================
echo       ALL V1 TESTS PASSED
echo ========================================
