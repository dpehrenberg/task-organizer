# task-organizer
currently here ==> Phase 1:
*tasks are stored in vector
*priority is set according to description length
*after each insertion the vector is being sorted

Phase 2:
*new task priority is determined by user prompt upon creation

Phase 3:
*new task priority is determined by linear comparisons with all existing tasks of the vector
*new task will take the priority which is the middle between its two adjacent priorities. If its the first it will take the value of 256. If it's the last, it will take the value of the panultimate task increased by 256.
*data structure that is efficient for erasing first member
*create cmake
*remember last task for undo operations
*add an option to show all tasks