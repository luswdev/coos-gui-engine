INCFLAG =\
-I. \
-Iinc \
-I../CoOS/inc \
-I../User/inc

CFLAGS += $(INCFLAG)

OBJS =\
$(OBJDIR)/app.o \
$(OBJDIR)/color.o \
$(OBJDIR)/dc.o \
$(OBJDIR)/dc_hw.o \
$(OBJDIR)/driver.o \
$(OBJDIR)/font.o \
$(OBJDIR)/server.o \
$(OBJDIR)/system.o \
$(OBJDIR)/title.o \
$(OBJDIR)/tm_stm32f4_fonts.o \
$(OBJDIR)/widget.o \
$(OBJDIR)/window.o

GIT_REMOTE = gui
GIT_BRANCH = mouse_dev

all: $(OBJS)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@echo "bulid file: $<"
	$(CC) $(CFLAGS) -MMD -MF$(@:%.o=%.d) -o $@ $< \
        && echo $(NOW) INFO Objecting $< success. >> ../build.log \
        || echo $(NOW) ERROR Objecting $< failed, stop building. >> ../build.log; exit 0

$(OBJDIR):
	@echo $(NOW) INFO Make new folder GUI/$(OBJDIR) >> ../build.log
	mkdir -p $(OBJDIR)

git:
	git add .
	git commit -m $(com_msg)
	git push -u $(GIT_REMOTE) $(GIT_BRANCH)

clean:
	-rm -rf $(OBJDIR)/*.o
	-rm -rf $(OBJDIR)/*.d
