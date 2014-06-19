# Makefile 0.1

TOOLS 		:= tools
MY_LS 		:= my_ls
CMD_ANA 	:= cmd_analyse
PRINT_LS 	:= print_ls
BIN_FILE 	:= a.out
OBJ_FILE 	:= $(MY_LS).o $(CMD_ANA).o $(PRINT_LS).o $(TOOLS).o

IDIR 		:= ./include
SDIR 		:= ./src
LINK_LIB 	:= -I$(IDIR)

# =============================================
# 目标文件
# =============================================
$(BIN_FILE) : $(OBJ_FILE)
	cc -o $(BIN_FILE) $(OBJ_FILE) $(LINK_LIB) -g
	make clean
# =============================================

# =============================================
# 编译过程
# =============================================
$(OBJ_FILE) : $(SDIR) $(IDIR)
	cc -c $(SDIR)/$(TOOLS).c $(LINK_LIB) -g
	cc -c $(SDIR)/$(MY_LS).c $(LINK_LIB) -g
	cc -c $(SDIR)/$(CMD_ANA).c $(LINK_LIB) -g
	cc -c $(SDIR)/$(PRINT_LS).c $(LINK_LIB) -g
# ============================================= 

.PHONY : clean

clean :
	-rm *.o
