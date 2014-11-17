ECHO %~dp0
@ECHO OFF
FOR /D %%G IN (..\sources\*) DO COPY standardTupfile %%G\Tupfile