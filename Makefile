CC=gcc
OUTPUTDIR=/custom-bin
CFLAGS+=-I/usr/include/postgresql -L/usr/lib/x86_64-linux-gnu -lpq
OBJS1=./src/extend-programmes/postgresQueryProgramme.o ./src/utils/postgresUtils.o  
OBJS2=./src/custom-agent/custom-agent-demon.o ./src/custom-objects/staticProgrammeVersion.o ./src/custom-objects/requiredDiskSpaceUsage.o  ./src/utils/diskSpaceUtils.o ./src/custom-objects/snmpSignal.o ./src/utils/postgresUtils.o
OBJS3=./src/extend-programmes/diskSpaceProgramme.o ./src/utils/diskSpaceUtils.o
OBJS4=./src/pass-programmes/disk-space-pass-programme.o ./src/utils/diskSpaceUtils.o
OBJS5=./src/pass-programmes/static-version-pass-programme.o
OBJS6=./src/pass-programmes/postgre-query-pass-programme.o ./src/utils/postgresUtils.o
BUILDAGENTLIBS=`net-snmp-config --agent-libs`
BUILDLIBS=`net-snmp-config --libs`
BUILDAGENTLIBS=`net-snmp-config --agent-libs`

TARGETS= disk-space-programme postgre-query-programme custom-agent-demon disk-space-pass-programme static-version-pass-programme postgre-query-pass-programme

all: $(TARGETS)

createdirectory: 
	mkdir -p $(OUTPUTDIR)

disk-space-programme: $(OBJS3) createdirectory
	gcc -o $(OUTPUTDIR)/disk-space-programme $(OBJS3)

postgre-query-programme: $(OBJS1) $(OUTPUTDIR)
	gcc -o $(OUTPUTDIR)/postgre-query-programme $(OBJS1) $(CFLAGS)

custom-agent-demon: $(OBJS2) $(OUTPUTDIR)
	$(CC) -o $(OUTPUTDIR)/custom-agent-demon $(OBJS2) $(CFLAGS) $(BUILDAGENTLIBS)

disk-space-pass-programme: $(OBJS4) $(OUTPUTDIR)
	gcc -o $(OUTPUTDIR)/disk-space-pass-programme $(OBJS4)

static-version-pass-programme: $(OBJS5) $(OUTPUTDIR)
	gcc -o $(OUTPUTDIR)/static-version-pass-programme  $(OBJS5)

postgre-query-pass-programme: $(OBJS6) $(OUTPUTDIR)
	gcc -o $(OUTPUTDIR)/postgre-query-pass-programme $(OBJS6) $(CFLAGS)

clean:
	rm ./src/*/*.o



