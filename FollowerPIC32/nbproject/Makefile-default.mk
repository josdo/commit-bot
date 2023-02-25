#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c FrameworkSource/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DistanceSensor.c FrameworkHeaders/TapeSensor.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/GoToBranchXFSM.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d ${OBJECTDIR}/FrameworkSource/ES_Port.o.d ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d ${OBJECTDIR}/FrameworkSource/terminal.o.d ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d ${OBJECTDIR}/FrameworkSource/dbprintf.o.d ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d ${OBJECTDIR}/ProjectSource/EventCheckers.o.d ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d ${OBJECTDIR}/ProjectSource/main.o.d ${OBJECTDIR}/ProjectSource/TemplateService.o.d ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o

# Source Files
SOURCEFILES=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c FrameworkSource/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DistanceSensor.c FrameworkHeaders/TapeSensor.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/GoToBranchXFSM.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX170F256B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/dc72f4b1444883b43703585ab19740ead0491669 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/411817f64bd84ab6d4a5685c8be2dd9c1b541574 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/370030ecd0d4984c392d39a6065044f6470b6aa7 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/1cd46d8ad900a505a749f9812b3ab416ae17dc2c .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/c05e1899f9016229b7514dcb24615e11d56812e3 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/fb371f5afb5fb7abc8587a889de32bc59b409da0 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/a2e877dc7dc0664d361147895149ed19e73f2a41 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/b920d5036393ae75ba39cd24222ce1b135e45d99 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/e33a08b90cf19236d88a6d1f08309e9d6af0d13d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/4dd421bf580012303f0e48a607d73cb2e2611eb7 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/e76435784fd53fcd022272477abf437989d8308f .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/c3b5f6eb3455f781f8c55248c89d5d1ed800f158 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/11a20cf80cd9974c57227a413ceda195eed9db8f .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/90eea809b40cef346778d7ecba13868754f7af97 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/20e8316a3e8002ef00480cf555afb172b1e92be1 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/5afb3d4a0dff530266bfa1ec33ffeb9b40a48d1f .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/f8f03f8be151fc398f5f905b7fae39e42520001d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/50ed5d10de18cbd6035384b5864e6a39fe9a0f9 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/81710c7f2d3aada3790952d850fde0065d139b42 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/740b4273380c27431fb27a73e32af7b33d566252 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/8010900a09829f5b1e0b776831ab2e138be2b394 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/5c383401873e1ca745f35f96f5f61c9eb3e374fd .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/937e133b30e4e6407a6ac3b803f0a7d52302c75a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o: FrameworkHeaders/GoToBranchXFSM.c  .generated_files/flags/default/e689b822799b7a467fe4e777ee37228c9eb0e78e .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o FrameworkHeaders/GoToBranchXFSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/4bea18a2ce4059e900bf29a1ae97c3d7848589fe .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/90004d82fb0244c5259efcd2e0b6988da111ab22 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/eba5842a9f8b11ceccee88142129964e429cb9d2 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/a8fcc962798e76ae4d4e65cb130e73c1441299bf .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/26302b3da34cf8f24b3be3fc25bcb378065824df .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/975a31b21209ddbee0b1261e3220093aa241b08a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/49ab50c2572fabfdeaecfcd638e29d0d6e649f1 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/53c3e220bf72478902fd99a6c33745b1fedb0ed .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/5ef5a4f309a1d10b3e0b439bed17c726b7b93983 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/60ad01557aa351dfdf50ff2773e0d9f5e704733e .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/873648558f9a3906afe041283f2d0655a7980f9a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/13d7a31d7aa888d9416518c190a232b9fbf35903 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/80671bbb6ba795f01690a517b065098dbdf6cf0c .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/246e7e0ab33192b79fcdb1cccf34be32554db7ca .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/8b4f102a28a6b81de5b6a17ef58382c37d67e310 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/ae97bda4062326aa94ca56bbb112882d00962f94 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/11232f361b37ff9c7e610b83f8cdd793ee38c72a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/17f507029ec82aeb4f3ea9b9aaae3dd26a07c7c .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/efdfc9e729c50a69535756064deff0ad0b334bb3 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/96a4e84241506298ac6b2f2101b64e7608db601 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/7b1b9a98c53f5cea34b664ad9c76fc0a15617b6b .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/511c2bbdeb5fef49ff06e566f5760dcfd759de8 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/ceced563ff6e0530db922869bb57c900d4fcdc3 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/94338aa72ea67aa9e55b90dd6a4b91a1ec51ac5d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/b7aa15dee2b050ba74eec29973967368b02e3891 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o: FrameworkHeaders/GoToBranchXFSM.c  .generated_files/flags/default/a697dd3ea04f046a5bc227162f58743249ad9bc4 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o FrameworkHeaders/GoToBranchXFSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/5ea6eb70953bcf925645117b7405dd33d71405fa .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/402b073ea2d7f903e4c635a5ce9c61fe4fd7a365 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c   -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -relaxed-math -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
