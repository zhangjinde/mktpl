######################################################################
# mktpl v2.0.0 - makefileģ���
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# ʹ�ù���makeobj.sh��makedir.sh�Զ����ɻ��д��С��makefile
# ��װ�ع��������ʵ��makefile
# �� Ȼ���ù���makelocal.sh���ػ�չ�����ɶ���ʹ��makefile
######################################################################

#################### Ŀ¼�ݹ��Ƶ����� ####################

#+ FILESYSTEM
# �ļ�ϵͳ��
CD		=	cd
RM		=	rm -f
CP		=	cp -f
MV		=	mv -f
MKDIR		=	mkdir -p
#- FILESYSTEM

#+ dir_all
# ����Ŀ���б�
all		:	make
#- dir_all

#+ dir_make
# make����
.PHONY:make
make	:
	ps
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_make

#+ dir_clean
# clean����
.PHONY:clean
clean	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) clean ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_clean

#+ dir_install
# install����
.PHONY:install
install	:
	@for i in $(DIROBJS) ; do \
		if [ -d "$$i" ] ; then \
			if [ -f "$$i/makefile$(MAKEFILE_POSTFIX)" ] ; then \
				$(CD) $$i ; \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) install ; \
				if [ $$? -ne 0 ] ; then \
					exit 1 ; \
				fi ; \
				$(CD) .. ; \
			fi ; \
		fi ; \
	done
#- dir_install