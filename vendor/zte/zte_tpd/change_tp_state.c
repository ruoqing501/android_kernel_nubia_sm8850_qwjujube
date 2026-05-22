#include "defs.h"

static const char * const lcdstate_to_str[3] = {
    "screen_on", "screen_off", "screen_in_doze"
};

static const char * const lcdchange_to_str[4] = {
    "lcd_exit_lp", "lcd_enter_lp", "lcd_on", "lcd_off"
};

void change_tp_state(int state)
{
    mutex_lock((struct mutex *)(tpd_cdev + 2824));
    if (state > 3 || current_lcd_state >= 3) {
        __break(0x5512);
        mutex_unlock((struct mutex *)(tpd_cdev + 2824));
        return;
    }
    pr_info("tpd_ufp_info: current_lcd_state:%s, lcd change:%s\n\n",
            lcdstate_to_str[current_lcd_state], lcdchange_to_str[state]);

    if (current_lcd_state == 2) {
        if (state == 0) {
            // Do nothing
        } else if (state == 2) {
            current_lcd_state = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9c0));
            ufp_tp_ops.field_8 = 0;
        } else if (state == 3) {
            current_lcd_state = 1;
            ufp_tp_ops.field_8 = 0;
            *(int *)((char *)&ufp_tp_ops + 128) = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9a0));
        } else {
            pr_err("tpd_ufp_err: ignore err lcd change\n");
        }
    } else if (current_lcd_state == 1) {
        if (state == 2) {
            current_lcd_state = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9c0));
            ufp_tp_ops.field_8 = 0;
        } else if (state == 1) {
            current_lcd_state = 2;
            ufp_tp_ops.field_8 = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9a0));
        } else {
            pr_err("tpd_ufp_err: ignore err lcd change\n");
        }
    } else if (current_lcd_state == 0) {
        if (state == 3) {
            current_lcd_state = 1;
            ufp_tp_ops.field_8 = 0;
            *(int *)((char *)&ufp_tp_ops + 128) = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9a0));
        } else if (state == 1) {
            current_lcd_state = 2;
            ufp_tp_ops.field_8 = 0;
            queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9a0));
        } else {
            pr_err("tpd_ufp_err: ignore err lcd change\n");
        }
    } else {
        current_lcd_state = 0;
        queue_work_on(32, *(struct workqueue_struct **)(tpd_cdev + 0x4b0), (struct work_struct *)(tpd_cdev + 0x9c0));
        ufp_tp_ops.field_8 = 0;
        pr_err("tpd_ufp_err: err lcd light change\n");
    }
    mutex_unlock((struct mutex *)(tpd_cdev + 2824));
}
