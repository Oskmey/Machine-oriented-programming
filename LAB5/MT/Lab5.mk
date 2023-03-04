##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Lab5
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/J/Documents/Documents
ProjectPath            :=C:/Users/J/Documents/Documents/Lab5
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/Lab5
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=J
Date                   :=04/03/2023
CodeLitePath           :=C:/cseapp/CodeLite
MakeDirCommand         :=mkdir
LinkerName             :=$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=C:/Users/J/Documents/Documents/build-$(WorkspaceConfiguration)/bin
OutputFile             :=..\build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc $(LibrarySwitch)c_nano 
ArLibs                 :=  "gcc" "c_nano" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-ar.exe rcu
CXX      := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
CC       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc.exe
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\cseapp\CodeLite
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=$(IntermediateDirectory)/GPIO.c$(ObjectSuffix) $(IntermediateDirectory)/Displaydriver.c$(ObjectSuffix) $(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) $(IntermediateDirectory)/startup.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  $(IntermediateDirectory)/$(ProjectName) $(IntermediateDirectory)/$(ProjectName).s19
	$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S $(IntermediateDirectory)/$(ProjectName) > $(IntermediateDirectory)/$(ProjectName).dass
	@echo Done

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GPIO.c$(ObjectSuffix): GPIO.c $(IntermediateDirectory)/GPIO.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/J/Documents/Documents/Lab5/GPIO.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GPIO.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GPIO.c$(DependSuffix): GPIO.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GPIO.c$(ObjectSuffix) -MF$(IntermediateDirectory)/GPIO.c$(DependSuffix) -MM GPIO.c

$(IntermediateDirectory)/GPIO.c$(PreprocessSuffix): GPIO.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GPIO.c$(PreprocessSuffix) GPIO.c

$(IntermediateDirectory)/Displaydriver.c$(ObjectSuffix): Displaydriver.c $(IntermediateDirectory)/Displaydriver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/J/Documents/Documents/Lab5/Displaydriver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Displaydriver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Displaydriver.c$(DependSuffix): Displaydriver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Displaydriver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Displaydriver.c$(DependSuffix) -MM Displaydriver.c

$(IntermediateDirectory)/Displaydriver.c$(PreprocessSuffix): Displaydriver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Displaydriver.c$(PreprocessSuffix) Displaydriver.c

$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix): KeyboardDriver.c $(IntermediateDirectory)/KeyboardDriver.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/J/Documents/Documents/Lab5/KeyboardDriver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KeyboardDriver.c$(DependSuffix): KeyboardDriver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KeyboardDriver.c$(DependSuffix) -MM KeyboardDriver.c

$(IntermediateDirectory)/KeyboardDriver.c$(PreprocessSuffix): KeyboardDriver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KeyboardDriver.c$(PreprocessSuffix) KeyboardDriver.c

$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c $(IntermediateDirectory)/startup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/J/Documents/Documents/Lab5/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(DependSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c

$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


