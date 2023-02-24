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
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/5f32fc5c193907871bf26dd1fd2bb038ede8a7e1 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/2e9dab66d8c1b493f04712f34f9ac4f22098885b .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/b8561f0380964d4ee3e5cd7c761d75e59e02f8a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/fe252567e8533ad0c1c0396ea643df5f3d467b91 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/f25ebae8c40e625b071df51642fd2d068ae80126 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/6c755dd6750d8369d7d6d25141624230799b56cd .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/cd7b91c01cbbfe090de07121f40a4d8af330cb18 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/86f69ebac7f367a13da363cb5f8eb8fee1dad357 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/b509ba595df648f38f64075c943a827ecab278aa .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/9c403c5ef67b24d0b53d1ea6c23f7cee5d026551 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/633fe813260b8c1446017db9a19df115e77a9ded .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/8d2a59976d61665177fca6bec2b8d50ee7f81881 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/31e25cf5ba70f12284db2ecc2832d3f5864f8671 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/15fd4e8be48a1f50c36dfa184654eaf6cde384a9 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/a4fcd2e7e0e960d2adaa58c8a22a3f027cd8a7e0 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/53a9e970db657a77a74360d3b956f591f94e42ed .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/b97a7bde8c0d80daa718d0d5a937ba7cf6fe2e27 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/44471da76ba5bc1e520181bb8118cf95cb5d246e .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/2acdc8ce75f69c31abb58cc45f86dcdfab625c7d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/3258a129439f56408f4081054bc8dccc1c7e5112 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/be688b54e185d0160d882c23096ccc855bfa1fda .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/84b642b9956c84a321459e90a4cc838f579c1b5e .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/35d17263bfd0c0b025ce25522be6203ae879715a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o: FrameworkHeaders/GoToBranchXFSM.c  .generated_files/flags/default/80898b158719e9124146ef0836df763bf92c020a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o FrameworkHeaders/GoToBranchXFSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/25446b8e30b78b24e4d2eab29e5431864651bc9d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/e84be9f3f907e2c72bcc2c823811e53d988cc2d3 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/ab9dfca7293e9b8f033185b243dd0126e407c8db .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/adefa1ba24f115e4c7acb1ceac9bfa4a56c10722 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/64927aacec7c3dac17041dfe9d57dd3728d357ad .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/ed088b213cf76369ddd46ffe92c84beead058953 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/dce83c49f5014235f0d0ba142209ad9af0562095 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/4077f8e20f17b63eaea38c213b4b59a7993b4cad .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/ef86bea3ea2c443cf8bdd24179bb983d0182139d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/9c8e7afbdc3915e2eabab5e349bbceec2351cdbe .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/3b2180203803e95c9e1a9e30ea1bbe47240cc982 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/4c0701c9490d481bc442636237c5cae9e99383a0 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/c262358cb921635dbe2c03120d70e110d8ce3bdd .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/c5941445e29a19bcb89706b251cd43f9bfdcd1c2 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/53fb8bae0f6ed972bab2dfac6a1db571f2cd96a7 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/c9b5b9b55f61a20afdb26f4a03b2ec3f623e3758 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/172d246ea1da11a785977144e011785807c59b94 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/e833afa249f25af95de6c9a27bb18545119e9e84 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/e97273d466816025b34451b4a6ff2f5c0083144d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/1cb178de15681cd98c7eaafc6ee69a700b26c431 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/90c662d1270702eae5551e9cfe22453fb10ec7c0 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/ac88f72df0df18449de2e3ff89fd72733d0d7300 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/8889a2f473b695434e87d41d12db95e0361ec24d .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/e481caccc9746380ebaa4efc1d78a7e8342b3a4e .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/68102e35d74ad38ac314f88a58457dc2e9576331 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o: FrameworkHeaders/GoToBranchXFSM.c  .generated_files/flags/default/4f624f3baed0a61363d0fc1ddc35b3b22090cf0a .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/GoToBranchXFSM.o FrameworkHeaders/GoToBranchXFSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/921023272a35298fd64c9a2e943ccbbcbcac2757 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/c73cbd19c04bb706ec24fd6508be7943be981099 .generated_files/flags/default/66e7c6a827ea0b0eafb9971d01f9570a50e9a598
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
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
