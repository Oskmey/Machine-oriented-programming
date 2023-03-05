##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=@@@@THE_LAB@@@@
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=C:/Users/oskar/Desktop/Chalmers/MOP/C/C
ProjectPath            :=C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=oskar
Date                   :=05/03/2023
CodeLitePath           :=C:/cseapp/CodeLite
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
OutputDirectory        :=$(IntermediateDirectory)
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="@@@@THE_LAB@@@@.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
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
Objects0=$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IntermediateDirectory)/Geometry.c$(ObjectSuffix) $(IntermediateDirectory)/Delay.c$(ObjectSuffix) $(IntermediateDirectory)/GraphicDriver.c$(ObjectSuffix) $(IntermediateDirectory)/AsciiDisplayDriver.c$(ObjectSuffix) $(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	C:\cseapp\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  Debug/@@@@THE_LAB@@@@ Debug/@@@@THE_LAB@@@@.s19
	C:\cseapp\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S Debug/@@@@THE_LAB@@@@ > Debug/@@@@THE_LAB@@@@.dass
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/startup.c$(ObjectSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/startup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/startup.c$(DependSuffix) -MM startup.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup.c$(PreprocessSuffix) startup.c

$(IntermediateDirectory)/Geometry.c$(ObjectSuffix): Geometry.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Geometry.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Geometry.c$(DependSuffix) -MM Geometry.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/Geometry.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Geometry.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Geometry.c$(PreprocessSuffix): Geometry.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Geometry.c$(PreprocessSuffix) Geometry.c

$(IntermediateDirectory)/Delay.c$(ObjectSuffix): Delay.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Delay.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Delay.c$(DependSuffix) -MM Delay.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/Delay.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Delay.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Delay.c$(PreprocessSuffix): Delay.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Delay.c$(PreprocessSuffix) Delay.c

$(IntermediateDirectory)/GraphicDriver.c$(ObjectSuffix): GraphicDriver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GraphicDriver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/GraphicDriver.c$(DependSuffix) -MM GraphicDriver.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/GraphicDriver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphicDriver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GraphicDriver.c$(PreprocessSuffix): GraphicDriver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GraphicDriver.c$(PreprocessSuffix) GraphicDriver.c

$(IntermediateDirectory)/AsciiDisplayDriver.c$(ObjectSuffix): AsciiDisplayDriver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/AsciiDisplayDriver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/AsciiDisplayDriver.c$(DependSuffix) -MM AsciiDisplayDriver.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/AsciiDisplayDriver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AsciiDisplayDriver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/AsciiDisplayDriver.c$(PreprocessSuffix): AsciiDisplayDriver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/AsciiDisplayDriver.c$(PreprocessSuffix) AsciiDisplayDriver.c

$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix): KeyboardDriver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/KeyboardDriver.c$(DependSuffix) -MM KeyboardDriver.c
	$(CC) $(SourceSwitch) "C:/Users/oskar/Desktop/Chalmers/MOP/C/C/@@@@THE_LAB@@@@/KeyboardDriver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/KeyboardDriver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/KeyboardDriver.c$(PreprocessSuffix): KeyboardDriver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/KeyboardDriver.c$(PreprocessSuffix) KeyboardDriver.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


