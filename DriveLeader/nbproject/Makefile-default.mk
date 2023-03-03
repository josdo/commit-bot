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
FINAL_IMAGE=${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DistanceSensor.c FrameworkHeaders/TapeSensor.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c ProjectHeaders/GoToBranchOriginSM.c ProjectSource/ComeBackSM.c ProjectSource/PushCommitSM.c ../Shared/EventOverSPI.c ../Shared/PIC32_SPI_HAL.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d ${OBJECTDIR}/FrameworkSource/ES_Port.o.d ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d ${OBJECTDIR}/FrameworkSource/terminal.o.d ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d ${OBJECTDIR}/FrameworkSource/dbprintf.o.d ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d ${OBJECTDIR}/ProjectSource/EventCheckers.o.d ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d ${OBJECTDIR}/ProjectSource/main.o.d ${OBJECTDIR}/ProjectSource/TemplateService.o.d ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o

# Source Files
SOURCEFILES=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DistanceSensor.c FrameworkHeaders/TapeSensor.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c ProjectHeaders/GoToBranchOriginSM.c ProjectSource/ComeBackSM.c ProjectSource/PushCommitSM.c ../Shared/EventOverSPI.c ../Shared/PIC32_SPI_HAL.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/87d8119ab340f1e219a99002a0b2cec7458342ae .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/eb9bcd13c2ee2180896969e464c1c8352805f396 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/2d265154804556cff4b8daa8610612ec5be75aaa .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/2f8e5f1a7b5c8bda9a09fecc0e63f96170115a42 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/fb675ecd8a2fa8bc48b54e0a881a5188f9914028 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/1d2a3a64634f7f360ed68c0844fef8b9645a6816 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/94950e7809dadd92dd9ee376b7e0a487d7e9333f .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/57d96606a05b665749ccfdb89de57e9a36d4dd44 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/9d61e04d2d44bdbc8d93e6ca3edb79bb58409d69 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/f60fe9c5fce9911dd14786c55e63a49e1adcaf8c .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/5b0bb3994588c607c3fc2dac993e1fe1060420e8 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/d958463f030f3a7400a30a853b7c7d38e896fd3f .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/e1e10453a056d30c670688302115f3997eaefae3 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/40adc62faf550ca0b967ab1d53047cc06f880aec .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/9edd52fad1e627e7fc98a058c8dbd23c6500fbb6 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/a756f7d4f24ef5dfe574bdd6af81c34603e47ac1 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/e81a49ca96ab878961fe8f7b6e1c8ca5486f289f .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/fd0c0b4e63bd133564d3a4ff9dbc0b69b20c2b5a .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/69cc66b28fdf299eb4fca3b6df0b4065341cc5b .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/59fb73c33fc32c9fc08dde81da8db379afd0428e .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/b8e3529c21527493206782c60cc02a686d624bb7 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/b0ea5412654c10e2277685f0f0deef8daf1263fe .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/e4615bcb47707a887d3e336029b11d64202c77c .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/8d6b4c635d6aab70b7e85b4013b6ae20aceee0db .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o: ProjectHeaders/GoToBranchOriginSM.c  .generated_files/flags/default/1f49e604fc36e5dab89e8215f8a239e05ee05c6 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectHeaders" 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d" -o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ProjectHeaders/GoToBranchOriginSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/ComeBackSM.o: ProjectSource/ComeBackSM.c  .generated_files/flags/default/df246049797de5ca5d2873b6e39c6c4cf1f12f70 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/ComeBackSM.o.d" -o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ProjectSource/ComeBackSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/PushCommitSM.o: ProjectSource/PushCommitSM.c  .generated_files/flags/default/eca34d23a52cadd46e3d631389d28bf7084d4d4f .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/PushCommitSM.o.d" -o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ProjectSource/PushCommitSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/EventOverSPI.o: ../Shared/EventOverSPI.c  .generated_files/flags/default/df90680d330c9b4500540d17eafc674b97790ed3 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d" -o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ../Shared/EventOverSPI.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o: ../Shared/PIC32_SPI_HAL.c  .generated_files/flags/default/704b306afe2873ec3985590a33e5a264873d5adc .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ../Shared/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/bd432ef9b9ea869d47771119b4a94fd12848061c .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/152f72f3c91073e697cc40c31c3e9973cf907a68 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/691b355814152a26e372ca5a98e1021de94582fe .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/132ffaf72aa2993e36076dbda92d764bf11b87fe .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/a0bf8682656b09e9f650a906407183445d26a3ae .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/6a594149b7efe098aee27bcad868be289df25988 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/75d7da1599b5f604c3f7cbb395c88255268ad651 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/fd26f51dc3fff354cff00d70cf4ebdceba5d4042 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/12bb67d6ad2a1f3e9cc12c2905d9e4f3aa7dd8fe .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/3d242c6d8e308d0152ef87864c753e49d70ad0dc .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/12c3f377777eda881c614204c408e04a7bf7c6d7 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/d33b90e6b74f21223e2a98922895149dedaff641 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/b4ba891866972258e738e75fda1b305f5a5e4106 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/3563e34034f476c79e1a56e3a53ea7b6525f3f0e .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/f54fc9018707f2317134d49c60ec1ef830ead0e0 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/3d795c8207c31b299b9f059c4ff85fcbaf00a71d .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/1b54835a7342963a37f834ee3d4dd7a7049015 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/DistanceSensor.o: ProjectSource/DistanceSensor.c  .generated_files/flags/default/f3890385c3c58ffe0d1ac34ac3d20ca0739aa9f3 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DistanceSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DistanceSensor.o.d" -o ${OBJECTDIR}/ProjectSource/DistanceSensor.o ProjectSource/DistanceSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TapeSensor.o: FrameworkHeaders/TapeSensor.c  .generated_files/flags/default/29d1b781f287be8a9f06e692b68eb13680037f43 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TapeSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TapeSensor.o FrameworkHeaders/TapeSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/6d0cb87b97e161e3da01e40b052ffebf598fafe1 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/160070c5ddccefbcd7e98e4403aadaaaefc20ccd .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/6f71c8d2ee6bde9e99564339c45475b5a3e3d877 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/6439c4b1cc548173dac73c47c882379e8796f183 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/ab6d70a531429ff83ccddd0e66d4ceeec380dec4 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o: ProjectHeaders/GoToBranchOriginSM.c  .generated_files/flags/default/bd0a9bd58b559066c70f6a96a1b3f3e3ec3b0df2 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectHeaders" 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d" -o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ProjectHeaders/GoToBranchOriginSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/ComeBackSM.o: ProjectSource/ComeBackSM.c  .generated_files/flags/default/52fa013f11e29fbc290ee59e747c82ae994e38e1 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/ComeBackSM.o.d" -o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ProjectSource/ComeBackSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/PushCommitSM.o: ProjectSource/PushCommitSM.c  .generated_files/flags/default/2e4ce85c8aa371f45bd1a92077becbea0f9e0a2e .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/PushCommitSM.o.d" -o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ProjectSource/PushCommitSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/EventOverSPI.o: ../Shared/EventOverSPI.c  .generated_files/flags/default/5aa653fb8fb074dd4afc30d56a37fa3335030200 .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d" -o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ../Shared/EventOverSPI.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o: ../Shared/PIC32_SPI_HAL.c  .generated_files/flags/default/85002de56db0e7aa81d62a687ff2a879f488d36e .generated_files/flags/default/71b3e7c91007fc7a03524b165e9a0428561612ef
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ../Shared/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/DriveLeader.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
