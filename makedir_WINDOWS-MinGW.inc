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
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_make

#+ dir_clean
# clean����
.PHONY:clean
clean	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) clean && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_clean

#+ dir_install
# install����
.PHONY:install
install	:
	@for %%i in ($(DIROBJS)) do ( \
		if exist %%i \
		( \
			if exist "%%i/makefile$(MAKEFILE_POSTFIX)" \
			( \
				$(CD) %%i && \
				$(MAKE) -f makefile$(MAKEFILE_POSTFIX) install && \
				$(CD) .. \
			) \
		) && \
		if not errorlevel 0 \
		( \
			exit \
		) \
	)
#- dir_install