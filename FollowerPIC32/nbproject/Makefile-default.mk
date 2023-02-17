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
SOURCEFILES_QUOTED_IF_SPACED=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c FrameworkSource/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DCMotorService.c ProjectSource/LeaderService.c FrameworkHeaders/OptoSensorService.c FrameworkHeaders/ButtonService.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DCMotorService.o ${OBJECTDIR}/ProjectSource/LeaderService.o ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o ${OBJECTDIR}/FrameworkHeaders/ButtonService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d ${OBJECTDIR}/FrameworkSource/ES_Port.o.d ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d ${OBJECTDIR}/FrameworkSource/terminal.o.d ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d ${OBJECTDIR}/FrameworkSource/dbprintf.o.d ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d ${OBJECTDIR}/ProjectSource/EventCheckers.o.d ${OBJECTDIR}/ProjectSource/main.o.d ${OBJECTDIR}/ProjectSource/TemplateService.o.d ${OBJECTDIR}/ProjectSource/DCMotorService.o.d ${OBJECTDIR}/ProjectSource/LeaderService.o.d ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o.d ${OBJECTDIR}/FrameworkHeaders/ButtonService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o ${OBJECTDIR}/FrameworkSource/dbprintf.o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/TemplateService.o ${OBJECTDIR}/ProjectSource/DCMotorService.o ${OBJECTDIR}/ProjectSource/LeaderService.o ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o ${OBJECTDIR}/FrameworkHeaders/ButtonService.o

# Source Files
SOURCEFILES=FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_Port.c FrameworkSource/ES_PostList.c FrameworkSource/ES_Queue.c FrameworkSource/ES_Timers.c FrameworkSource/terminal.c FrameworkSource/circular_buffer_no_modulo_threadsafe.c FrameworkSource/dbprintf.c FrameworkSource/PIC32PortHAL.c FrameworkSource/PIC32_AD_Lib.c FrameworkSource/PIC32_SPI_HAL.c ProjectSource/EventCheckers.c ProjectSource/main.c ProjectSource/TemplateService.c ProjectSource/DCMotorService.c ProjectSource/LeaderService.c FrameworkHeaders/OptoSensorService.c FrameworkHeaders/ButtonService.c



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
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/56992ada2ff0c8f1ca1d80c471bc3b044d2dffda .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/8cce81e8f840ba996403c66f4bed0ab659baca49 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/e79e4a743999bf063838f78b27e9300268859cf9 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/b92168f26c951ce04f467bf52997cf435b3ce22 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/1c20a090c2c2a6020d0824a2bb04de77717bd245 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/64047bc77498b5cd9c80df7d932e81ed0e492523 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/9b3a2cac896eaf72027fe9c948fe3604d0292cb5 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/59a3a344b3f0e027db620e38aaefff0d1a4bd62d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/8aaa452b14e7ad0b07c9d5ab29fa6306e67380c2 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/759aea6ab2d51e80be5f44a43f27a241e5eeb5cc .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/53fc8c8771195752c7fde8b259d53a5eaee7fc8c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/2985ec93958021f57ff0b4f141cc7ea38e8e3ab7 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/714828c49d8284bb68dcadf7b340500266e19c10 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/704dab9adc33a88222240947222df84ef626f7d2 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/9480199e893aaa61a92500177795e437d314fd03 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/7cfcff4dd6cea7f0801394477e3bcef8fd01cb1c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/a5267028bad7227d76d63e5892f985134a0f0e2d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/DCMotorService.o: ProjectSource/DCMotorService.c  .generated_files/flags/default/cd6e4b9a5dcc54d46ee4d0f75af8f26a8fab7d5d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DCMotorService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DCMotorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DCMotorService.o.d" -o ${OBJECTDIR}/ProjectSource/DCMotorService.o ProjectSource/DCMotorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/LeaderService.o: ProjectSource/LeaderService.c  .generated_files/flags/default/86902863ccbda9fb2774395dc7f7e07f5a797d2a .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/LeaderService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/LeaderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/LeaderService.o.d" -o ${OBJECTDIR}/ProjectSource/LeaderService.o ProjectSource/LeaderService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o: FrameworkHeaders/OptoSensorService.c  .generated_files/flags/default/d8a83f4cd2cd21ebed3ba31fd59ed557b2acbc46 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o.d" -o ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o FrameworkHeaders/OptoSensorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/ButtonService.o: FrameworkHeaders/ButtonService.c  .generated_files/flags/default/8e0764198061bb81186ec6f8b7201d3114c6062d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/ButtonService.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/ButtonService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/ButtonService.o.d" -o ${OBJECTDIR}/FrameworkHeaders/ButtonService.o FrameworkHeaders/ButtonService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  .generated_files/flags/default/f035dcf9d8bffd99a99bc5556cd7d8ebb76c92d2 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  .generated_files/flags/default/e2d38b0b81284697c6e156e618f50b79a07af7c7 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  .generated_files/flags/default/4e27f367f57c6579bb53d2fab55d554fa9f8f4c5 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  .generated_files/flags/default/5574cc76a5935cd097eb51bb7d7dd0a6352809e7 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  .generated_files/flags/default/8335cb9845790cb4a3dc192784641764ae02fc6c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  .generated_files/flags/default/7f5042cb5d31b7593d4ee388c3bc76d6219b41d .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  .generated_files/flags/default/58a96217724ee78fbe2c539cb755480ff2226c3a .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  .generated_files/flags/default/52db9f45e6ded540528cd55d7fbec8c34997b280 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  .generated_files/flags/default/3de4bb0178c5a87190974433f001cd049816ccd2 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o: FrameworkSource/circular_buffer_no_modulo_threadsafe.c  .generated_files/flags/default/150e147136b297e29679474191cdc59e49ed442c .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o.d" -o ${OBJECTDIR}/FrameworkSource/circular_buffer_no_modulo_threadsafe.o FrameworkSource/circular_buffer_no_modulo_threadsafe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/dbprintf.o: FrameworkSource/dbprintf.c  .generated_files/flags/default/2b66ffc904205fd3946e5d21a396e53dbd89e6e8 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/dbprintf.o.d" -o ${OBJECTDIR}/FrameworkSource/dbprintf.o FrameworkSource/dbprintf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o: FrameworkSource/PIC32PortHAL.c  .generated_files/flags/default/21e67ee14a73331fbff69003f1efaecc1ae1f269 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32PortHAL.o FrameworkSource/PIC32PortHAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o: FrameworkSource/PIC32_AD_Lib.c  .generated_files/flags/default/1209f7bc1314407f99feedd941e0526f9920648e .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_AD_Lib.o FrameworkSource/PIC32_AD_Lib.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o: FrameworkSource/PIC32_SPI_HAL.c  .generated_files/flags/default/30ea5d9d86ce83cc1f8e2662431adc33dc24a322 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o.d" -o ${OBJECTDIR}/FrameworkSource/PIC32_SPI_HAL.o FrameworkSource/PIC32_SPI_HAL.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  .generated_files/flags/default/f5d4f9b7069262275a1db666d3a04276ca9da5ff .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  .generated_files/flags/default/1cb999d637b3d301f36bfc3add8a849a123c7552 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/TemplateService.o: ProjectSource/TemplateService.c  .generated_files/flags/default/24cbe3bcad5957ed45d7bb1a8d17f1027b69b548 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/TemplateService.o.d" -o ${OBJECTDIR}/ProjectSource/TemplateService.o ProjectSource/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/DCMotorService.o: ProjectSource/DCMotorService.c  .generated_files/flags/default/d05b504c27dae0759233012d412e7ca7cb4a1cc .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/DCMotorService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/DCMotorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/DCMotorService.o.d" -o ${OBJECTDIR}/ProjectSource/DCMotorService.o ProjectSource/DCMotorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ProjectSource/LeaderService.o: ProjectSource/LeaderService.c  .generated_files/flags/default/d07e8190e5dff3a296cfb03ebf4887c776bc5894 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/LeaderService.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/LeaderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/ProjectSource/LeaderService.o.d" -o ${OBJECTDIR}/ProjectSource/LeaderService.o ProjectSource/LeaderService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o: FrameworkHeaders/OptoSensorService.c  .generated_files/flags/default/c7fa07c025a51ca6268d5775fa562c5a7e1ec7e6 .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o.d" -o ${OBJECTDIR}/FrameworkHeaders/OptoSensorService.o FrameworkHeaders/OptoSensorService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FrameworkHeaders/ButtonService.o: FrameworkHeaders/ButtonService.c  .generated_files/flags/default/5789946e4d52dd2d33313b936cd166946f170a9b .generated_files/flags/default/444dd6797b527ec6f4a935221adf8da7c2494839
	@${MKDIR} "${OBJECTDIR}/FrameworkHeaders" 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/ButtonService.o.d 
	@${RM} ${OBJECTDIR}/FrameworkHeaders/ButtonService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"FrameworkHeaders" -I"ProjectHeaders" -fno-common -MP -MMD -MF "${OBJECTDIR}/FrameworkHeaders/ButtonService.o.d" -o ${OBJECTDIR}/FrameworkHeaders/ButtonService.o FrameworkHeaders/ButtonService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/FollowerPIC32.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=256,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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
