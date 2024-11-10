	.syntax unified
	.cpu cortex-m4
	.fpu softvfp
	.global Os_SchedulerLaunch
	.extern Os_CurrentTCB

	.text
	.thumb
	.thumb_func
	.type	Os_SchedulerLaunch, %function
Os_SchedulerLaunch:
	.cfi_startproc
	CPSID I						/* Disable global exceptions */

	LDR R0, =Os_CurrentTCB		/* R0 = address of Os_CurrentTCB pointer */
	LDR R2, [R0]				/* R2 = address of TCB */

	LDR SP, [R2]				/* SP = stackPtr of TCB */
	POP {R4-R11}				/* Pop values at SP to R4, R5, R6, R7, R8, R9, R10, R11 */
	POP {R0-R3}					/* Pop values at SP to R0, R1, R2, R3 */
	POP {R12}					/* Pop values at SP R12 */
	ADD SP, SP, #4				/* Skip LR value by decreasing 4 bytes */
	POP {LR}					/* Pop values(PC) at LR */
	ADD SP, SP, #4				/* Skip xPSR value by decreasing 4 bytes */

	CPSIE I						/* Enable global exceptions */

	BX LR						/* Jump to the first task */

	.cfi_endproc


	.align	2
	.global	PendSV_Handler
	.extern Os_SchedulerRoundRobin
	.thumb
	.thumb_func
	.type	PendSV_Handler, %function
PendSV_Handler:
	CPSID I						/* Disable global exceptions */
	PUSH {R4-R11}				/* Store R4-R11 registers to stack */
	LDR R0, =Os_CurrentTCB			/* R0 = address of Os_CurrentTCB pointer */
	LDR R1, [R0]				/* R1 = address of TCB */

	STR SP, [R1]				/* stackPtr = SP */

	PUSH {R0, LR}				/* Push address of Os_CurrentTCB and LR */
	BL Os_SchedulerRoundRobin	/* Call Os_SchedulerRoundRobin */
	POP {R0, LR}				/* Pop address of Os_CurrentTCB and LR */
	LDR R1, [R0]				/* R1 = address of TCB */

	LDR SP, [R1]				/* SP = stackPtr */
	POP {R4-R11}				/* Restore R4-R11 into register bank before exiting exception */
	CPSIE I						/* Enable global exceptions */
	BX LR						/* Return from exception */
