Set oShell = WScript.CreateObject("WScript.Shell")
sDesktop = oShell.SpecialFolders("Desktop")
Set oLink = oShell.CreateShortcut(sDesktop & "\MiniWargame Web.lnk")
oLink.TargetPath = "c:\Users\mst\Desktop\Dev\Wahh40k\launch_web_game.bat"
oLink.WorkingDirectory = "c:\Users\mst\Desktop\Dev\Wahh40k"
oLink.IconLocation = "c:\Windows\System32\shell32.dll,1"
oLink.Save
