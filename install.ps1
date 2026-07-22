#Requires -Version 5.1
<#
    CppMaster Console — one-line installer/launcher.

    Usage (once the repo is public):
        irm https://raw.githubusercontent.com/Layellie/cppmaster-console/master/install.ps1 | iex

    Downloads the latest standalone build (statically-linked, no Visual
    C++ Redistributable required) from the repo's "latest" GitHub
    Release, saves it under %LOCALAPPDATA% so progress persists across
    runs, and launches it immediately.
#>

$ErrorActionPreference = "Stop"

$releaseUrl = "https://github.com/Layellie/cppmaster-console/releases/download/latest/CppMasterConsole.exe"
$installDir = Join-Path $env:LOCALAPPDATA "CppMasterConsole"
$exePath = Join-Path $installDir "CppMasterConsole.exe"

New-Item -ItemType Directory -Force -Path $installDir | Out-Null

Write-Host "CppMaster Console indiriliyor..." -ForegroundColor Cyan
Invoke-WebRequest -Uri $releaseUrl -OutFile $exePath -UseBasicParsing

Write-Host "Başlatılıyor..." -ForegroundColor Cyan
Push-Location $installDir
try {
    & $exePath
} finally {
    Pop-Location
}
