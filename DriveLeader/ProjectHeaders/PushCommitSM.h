#ifndef PushCommitSM_H
#define PushCommitSM_H

typedef enum {
    ROTATE_TO_FACE_BRANCH,
            STOP_PUSH_COMMIT,
            MOVE_FORWARD
} PushCommitSMState_t;

ES_Event_t RunPushCommitSM(ES_Event_t CurrentEvent);
void StartPushCommitSM(ES_Event_t CurrentEvent);
PushCommitSMState_t QueryPushCommit(void);

#endif