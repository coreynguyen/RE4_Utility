@echo off
rem The four lines below will give you reliable YY DD MM YYYY HH Min Sec MS variables in XP Pro and higher.

for /f "tokens=2 delims==" %%a in ('wmic OS Get localdatetime /value') do set "dt=%%a"
set "YY=%dt:~2,2%" & set "YYYY=%dt:~0,4%" & set "MM=%dt:~4,2%" & set "DD=%dt:~6,2%"
set "HH=%dt:~8,2%" & set "Min=%dt:~10,2%" & set "Sec=%dt:~12,2%" & set "MS=%dt:~15,3%"
set "datestamp=%YYYY%-%MM%-%DD%"


>"%~dp0\\include\version.h" echo #ifndef appver_h
>>"%~dp0\\include\version.h" echo #define appver_h
>>"%~dp0\\include\version.h" echo constexpr char const* appver = "RE4 Utility (Build: %datestamp%)";
>>"%~dp0\\include\version.h" echo #endif