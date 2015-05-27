#!/bin/bash

############################################################
# makelocal  - makefileģ��⹤��
# copyright by calvin 2013
# calvinwilliams.c@gmail.com
#
# ����Сmakefile�ļ����ػ�չ����ָ��Ŀ��ϵͳ��չ���ɿɶ���ʹ��makefile
# �﷨ : makelocal.sh [ OS ]
# ��ע : OS������Linux��AIX��֧�ֻ�������ָ��all�������л���makefile
#        ��ָ��OS��������ȡ��������MKTPLOS
############################################################

EXPAND_TABLE=""

ExpandMacro()
{
	local INFILE=$1
	local MACRO=$2
	local OUTFILE=$3
	local MACROBAK=""
	
	echo $EXPAND_TABLE | grep -w $MACRO > /dev/null
	R=$?
	if [ $R -eq 0 ] ; then
		return
	else
		EXPAND_TABLE="${EXPAND_TABLE} ${MACRO}"
	fi
	
	LINENUMBER=`grep -E -w -n "^\#\+ ${MACRO}" "${INFILE}" | awk -F: '{print $1}'`
	if [ $? -ne 0 -o "$LINENUMBER" -le 0 ] ; then
		return
	fi
	
	LINES=1
	IN_EXPAND_SECTION=0
	while read -r LINE2 ; do
		if [ $IN_EXPAND_SECTION -eq 0 ] ; then
			if [ $LINES -eq $LINENUMBER ] ; then
				IN_EXPAND_SECTION=1
				continue
			fi
			
			LINES=`expr $LINES + 1`
			continue
		fi
		
		FIELD1=`echo $LINE2 | awk '{print $1}'`
		FIELD2=`echo $LINE2 | awk '{print $2}'`
		
		if [ x"$FIELD1" = x"#@" ] ; then
			MACROBAK=$MACRO
			ExpandMacro "$INFILE" "$FIELD2" "$OUTFILE"
			echo ""
			MACRO=$MACROBAK
		elif [ x"$FIELD1" = x"#-" -a x"$FIELD2" = x"$MACRO" ] ; then
			break
		else
			echo "$LINE2"
		fi
	done < $INFILE >> $OUTFILE
}

OS=$1

if [ ! -f makefile ] ; then
	echo "makefile������"
	exit 0
fi

if [ x"$OS" = x"" ] ; then
	OS=${MKTPLOS}
elif [ x"$OS" = x"all" ] ; then
	OS='*'
fi

grep "include \$(MKTPLDIR)/makeobj_\$(MKTPLOS).inc" makefile > /dev/null
if [ $? -eq 0 ] ; then
	OBJ_OR_DIR="obj"
else
	grep "include \$(MKTPLDIR)/makedir_\$(MKTPLOS).inc" makefile > /dev/null
	if [ $? -eq 0 ] ; then
		OBJ_OR_DIR="dir"
	fi
fi

for FILE in `ls ${MKTPLDIR}/make${OBJ_OR_DIR}_${OS}.inc` ; do
	OS=`basename $FILE | tr '_.' '  ' | awk '{print $2}'`
	
	EXPAND_TABLE=""
	
	printf "# ���ļ���makelocal.sh�Զ�����\n" > makefile.${OS}
	if [ x"${OS}" = x"*" ] ; then
		MAKEFILE_POSTFIX=""
	else
		MAKEFILE_POSTFIX=".${OS}"
	fi
	printf "MAKEFILE_POSTFIX=$MAKEFILE_POSTFIX\n" >> makefile.${OS}
	
	IFS=
	while read -r LINE1 ; do
		FIELD1=`echo $LINE1 | awk '{print $1}'`
		FIELD2=`echo $LINE1 | awk '{print $2}'`
		if [ x"$LINE1" = x"include \$(MKTPLDIR)/make${OBJ_OR_DIR}_\$(MKTPLOS).inc" ] ; then
			continue
		elif [ x"$FIELD1" = x"#@" ] ; then
			ExpandMacro "$FILE" "$FIELD2" "makefile.${OS}"
			echo ""
		else
			echo $LINE1
		fi
	done < makefile >> makefile.${OS}
	unset IFS
done

