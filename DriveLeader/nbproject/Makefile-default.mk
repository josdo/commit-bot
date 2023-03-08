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
SOURCEFILES_QUOTED_IF_SPACED=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c ../Shared/EventOverSPI.c ../Shared/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c ProjectHeaders/GoToBranchOriginSM.c ProjectSource/ComeBackSM.c ProjectSource/PushCommitSM.c ProjectSource/Timer5.c FrameworkHeaders/AdjustButtons.c FrameworkHeaders/DistanceSlider.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ${OBJECTDIR}/ProjectSource/Timer5.o ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d ${OBJECTDIR}/FrameworkSource/ES_Port.o.d ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d ${OBJECTDIR}/FrameworkSource/terminal.o.d ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d ${OBJECTDIR}/FrameworkSource/dbprintf.o.d ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d ${OBJECTDIR}/ProjectSource/EventCheckers.o.d ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d ${OBJECTDIR}/ProjectSource/main.o.d ${OBJECTDIR}/ProjectSource/TemplateService.o.d ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d ${OBJECTDIR}/ProjectSource/Timer5.o.d ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o.d ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ${OBJECTDIR}/ProjectSource/Timer5.o ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o

# Source Files
SOURCEFILES=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c ../Shared/EventOverSPI.c ../Shared/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/main.c ProjectSource/TemplateService.c FrameworkHeaders/BeaconSensor.c FrameworkHeaders/InitTimer2.c FrameworkHeaders/DCMotor.c FrameworkHeaders/TopHSM.c FrameworkHeaders/CalibrationSM.c ProjectHeaders/GoToBranchOriginSM.c ProjectSource/ComeBackSM.c ProjectSource/PushCommitSM.c ProjectSource/Timer5.c FrameworkHeaders/AdjustButtons.c FrameworkHeaders/DistanceSlider.c



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
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/a5c1e505e9b95a7486afa1046da076a6ac62392c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/45582ef907aafa1c372cdbdb4dc69352290b7cfc .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/bfaf81d2dbf5f9589ffa375c66a4f7bd1e4c49c0 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/3feca5cb602738c1418ccbc46fb7d94a5d735a68 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/b7371e0d55dd4f252ca5b9fdc56468cb2a9b7104 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/af8e07ab58ae9e54e44dab23f2a73a97da42b103 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/f60124114b58dbd81cef442f2ab847feb693c472 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/22e3cf5dad282aad5768e015d667a5a0742f6d38 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/a25554318652237af351fcb1e8cda228058bf0b5 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/1ee4c022d6133996c4e4fa7a9724e12bb17b2fa1 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/66d03d9eb16a84a456f0a9b17439cae47e1cf99e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/478998a322447ca234cc8ace06a806153444da3d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/be509a54e0eb87fab16c448ec976545a7c9bf32f .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/EventOverSPI.o: ../Shared/EventOverSPI.c  .generated_files/flags/default/54d2452ccb912330a7b661c5482d8f56c21d4f .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d" -o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ../Shared/EventOverSPI.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o: ../Shared/PIC32_SPI_HAL.c  .generated_files/flags/default/9aef2eed642e3b1a7862387268dd5ce61e500ea4 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ../Shared/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/eb366d326aa38fbb2c0234a15128cbb5408eda3c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/517d80ff332e730da101be52ba954bc07973fc10 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/a3a8c37a70f669b2baae66d60b9abb1d66f55458 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/ad1438d4b3b7ee3eea6c62802dc9da31be66c4a3 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/96f0b9310033a863ffbccc8a2f667adea8b49f1e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/be446dd99492a34b3dae7ed3c49d84bdc0c0ab5b .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/59bd4b009d22f9cfc34b9613d66f2a81b57cf0dc .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/21508635eb9f77e6ad72019db0ca0eca0961a1f1 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/1348722fa9d4a70de77dc1d04deda7042a08c3c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o: ProjectHeaders/GoToBranchOriginSM.c  .generated_files/flags/default/23951899c6fe9ec409e5f6d8439ebd23644c8eb6 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectHeaders" 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d" -o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ProjectHeaders/GoToBranchOriginSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/ComeBackSM.o: ProjectSource/ComeBackSM.c  .generated_files/flags/default/361be0bc0f5d66a6560221d8a9af7a3153ff4548 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/ComeBackSM.o.d" -o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ProjectSource/ComeBackSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/PushCommitSM.o: ProjectSource/PushCommitSM.c  .generated_files/flags/default/7de4d20949d96dc6d86b1dcf00e0cfeebd9c4f4c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/PushCommitSM.o.d" -o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ProjectSource/PushCommitSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/Timer5.o: ProjectSource/Timer5.c  .generated_files/flags/default/3627b770c79501ba45a3f034d86211f9e102a069 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/Timer5.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/Timer5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/Timer5.o.d" -o ${OBJECTDIR}/ProjectSource/Timer5.o ProjectSource/Timer5.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o: FrameworkHeaders/AdjustButtons.c  .generated_files/flags/default/35899321b44c407b1b89520f7473ba0b12f3d93e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o.d" -o ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o FrameworkHeaders/AdjustButtons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o: FrameworkHeaders/DistanceSlider.c  .generated_files/flags/default/81eb46e9aa8818230f472cb12fa66b6e761bec8a .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o FrameworkHeaders/DistanceSlider.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/d4b49e594f4b6861c9a8a68ddad3524e54d58911 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/a63f694c8f5b5c152c75354a6f5d12a7b5488c9b .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/c3899ddcb90073c6b53ee1571ace7e09286e3af7 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/75205c9ebd02c6c7bb2d266dc82f2113cdec2136 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/e26f77a5a1e9fa87ace694ec73f21d5c7253dd7 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/6116188bd7b5596ab252d5e1ca56bbc09a282c9b .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/fd3f09ebc83eaf01b3a89d3bd861fe9fa72b6667 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/845b6f7f926bf0a369ecf25504339c231a3d956f .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/3a2ffc5cc03e77fad0306a6a56f8037b9c652b9e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/e4f4af8e49b3c6313fcd787b9a29a241b7a506ed .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/a0efb37cd74ac7addca44f5634df09f0078dfa23 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/614f5dd55714daf9c0b6ef82f9f5b944634dd1aa .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/63471c1c2dbaf53563b49c7af5c49134c900a898 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/EventOverSPI.o: ../Shared/EventOverSPI.c  .generated_files/flags/default/2afef68545942e140e2f6faac56fdba88d4ca209 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/EventOverSPI.o.d" -o ${OBJECTDIR}/_ext/1735361612/EventOverSPI.o ../Shared/EventOverSPI.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o: ../Shared/PIC32_SPI_HAL.c  .generated_files/flags/default/b636cb9881088a4e117b1aaf0c11ac84e8d7bdba .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/_ext/1735361612" 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/_ext/1735361612/PIC32_SPI_HAL.o ../Shared/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/e15b525d65b3a52272d7fa4c40e031fe14e909cc .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  .generated_files/flags/default/1cff21e4ba5cfe2131f9d805c6fdf55c79d6d252 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/a9d666b6528fb851de4e8a67add5260908905d72 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/e37546da69642b25428c465cc1f332c410a9712b .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o: FrameworkHeaders/BeaconSensor.c  .generated_files/flags/default/f2f6f9351e8bb6d223dc69ea57d78e57390c751 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/BeaconSensor.o FrameworkHeaders/BeaconSensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/InitTimer2.o: FrameworkHeaders/InitTimer2.c  .generated_files/flags/default/49cf42ffb2d1e6d0d14c4bcc38cc382c1ff68c3c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/InitTimer2.o.d" -o ${OBJECTDIR}/FrameworkHeaders/InitTimer2.o FrameworkHeaders/InitTimer2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DCMotor.o: FrameworkHeaders/DCMotor.c  .generated_files/flags/default/12970694a58f40472dc118f442977e46f2c2a8f .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DCMotor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DCMotor.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DCMotor.o FrameworkHeaders/DCMotor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/TopHSM.o: FrameworkHeaders/TopHSM.c  .generated_files/flags/default/92e8d45b3b96bfcd6daa210152c1567c82fb0a34 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/TopHSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/TopHSM.o FrameworkHeaders/TopHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o: FrameworkHeaders/CalibrationSM.c  .generated_files/flags/default/e0cfcee4f9e3ebfdc66684e53644a55148b2723e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o.d" -o ${OBJECTDIR}/FrameworkHeaders/CalibrationSM.o FrameworkHeaders/CalibrationSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o: ProjectHeaders/GoToBranchOriginSM.c  .generated_files/flags/default/d42abf5a1cfddf8c74d20911e564fc5703e79e0d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectHeaders" 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o.d" -o ${OBJECTDIR}/ProjectHeaders/GoToBranchOriginSM.o ProjectHeaders/GoToBranchOriginSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/ComeBackSM.o: ProjectSource/ComeBackSM.c  .generated_files/flags/default/c4979a0ca8e9afc08bb6f6fd9c6c4b8823fbc8b9 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/ComeBackSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/ComeBackSM.o.d" -o ${OBJECTDIR}/ProjectSource/ComeBackSM.o ProjectSource/ComeBackSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/PushCommitSM.o: ProjectSource/PushCommitSM.c  .generated_files/flags/default/7444bc09348172f9911411f7eae04d507d2d8783 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/PushCommitSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/PushCommitSM.o.d" -o ${OBJECTDIR}/ProjectSource/PushCommitSM.o ProjectSource/PushCommitSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/Timer5.o: ProjectSource/Timer5.c  .generated_files/flags/default/c45d4756d2c954485249ce9c68fd88078c7fefb3 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/Timer5.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/Timer5.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/Timer5.o.d" -o ${OBJECTDIR}/ProjectSource/Timer5.o ProjectSource/Timer5.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o: FrameworkHeaders/AdjustButtons.c  .generated_files/flags/default/c4ab574d3e088a4b9275aef5fa95e05d57f1dc5e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o.d" -o ${OBJECTDIR}/FrameworkHeaders/AdjustButtons.o FrameworkHeaders/AdjustButtons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o: FrameworkHeaders/DistanceSlider.c  .generated_files/flags/default/617d8cfc625e0849271786b6ef156a9a54431c3c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o.d" -o ${OBJECTDIR}/FrameworkHeaders/DistanceSlider.o FrameworkHeaders/DistanceSlider.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
