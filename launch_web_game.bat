@echo off
pushd "c:\Users\mst\Desktop\Dev\Wahh40k\Wahh40k_Web"
start "MiniWargame Server" cmd /c "npm start"
timeout /t 1 >nul
start "" "http://localhost:3000"
popd
exit /b
