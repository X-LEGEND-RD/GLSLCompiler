@for %%s in (*.vert) do ..\bin\GLSLCompiler.Release.x64.exe --dump-spirv-validation --version 450 %%s
@for %%s in (*.frag) do ..\bin\GLSLCompiler.Release.x64.exe --dump-spirv-validation --version 450 %%s
@pause