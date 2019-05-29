/**
 *******************************************************************************
 * @file       dcHw.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

static void DcHwDrawPoint(struct rtgui_dc *dc, int x, int y);
static void DcHwDrawColorPoint(struct rtgui_dc *dc, int x, int y, rtgui_color_t color);
static void DcHwDrawVline(struct rtgui_dc *dc, int x, int y1, int y2);
static void DcHwDrawHline(struct rtgui_dc *dc, int x1, int x2, int y);
static void DcHwFillRect(struct rtgui_dc *dc, rtgui_rect_t *rect);
static void DcHwBlitLine(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data);
static void DcHwBlit(struct rtgui_dc *dc, struct rtgui_point *dc_point, struct rtgui_dc *dest, rtgui_rect_t *rect);
static StatusType DcHwFini(struct rtgui_dc *dc);

const GuiDcEng dcHwEngine =
{
    DcHwDrawPoint,
    DcHwDrawColorPoint,
    DcHwDrawVline,
    DcHwDrawHline,
    DcHwFillRect,
    DcHwBlitLine,
    DcHwBlit,

    DcHwFini,
};

P_GuiDc DcHwCreate(P_GuiWidget owner)
{
    struct dcHw *dc;

    /* adjudge owner */
    if (owner==Co_NULL || owner->toplevel==Co_NULL){
        return Co_NULL;
    }

    /* create DC */
    dc = (struct dcHw *) GuiMalloc(sizeof(struct dcHw));
    if (dc)
    {
        dc->parent.type = GUI_DC_HW;
        dc->parent.engine = &dc_hw_engine;
        dc->owner = owner;
        dc->hwDriver = GraphiDriverGetDefault();

        return &(dc->parent);
    }

    return Co_NULL;
}

static StatusType DcHwFini(P_GuiDc dc)
{
    if (dc==Co_NULL || dc->type!=GUI_DC_HW){
        return Co_FALSE;
    }

    /* release hardware dc */
    GuiFree(dc);

    return Co_TRUE;
}

/* draw a logic point on device */
static void DcHwDrawPoint(struct rtgui_dc *self, int x, int y)
{
    struct dcHw *dc;

    if(self!=Co_NULL){
        return;
    }

    dc = (struct dcHw *) self;

    if (x < 0 || y < 0){
        return;
    }

    x = x + dc->owner->extent.x1;
    if (x >= dc->owner->extent.x2){
        return;
    }
    y = y + dc->owner->extent.y1;
    if (y >= dc->owner->extent.y2){
        return;
    }

    /* draw this point */
    dc->hw_driver->ops->setPixel(&(dc->owner->gc.foreground), x, y);
}

static void DcHwDrawColorPoint(struct rtgui_dc *dc, int x, int y, rtgui_color_t color);
static void DcHwDrawVline(struct rtgui_dc *dc, int x, int y1, int y2);
static void DcHwDrawHline(struct rtgui_dc *dc, int x1, int x2, int y);
static void DcHwFillRect(struct rtgui_dc *dc, rtgui_rect_t *rect);
static void DcHwBlitLine(struct rtgui_dc *self, int x1, int x2, int y, rt_uint8_t *line_data);
static void DcHwBlit(struct rtgui_dc *dc, struct rtgui_point *dc_point, struct rtgui_dc *dest, rtgui_rect_t *rect);