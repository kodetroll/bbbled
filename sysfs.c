/*************************************************************************
 * sysfs.c - A simple c library to implement gpio pin control using sysfs
 * from userspace on the Beagle Bone Black.
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

#include "sysfs.h"
 
//	/sys/class/gpio/...

//char gpio[] = "/sys/class/gpio";
char sysfs[120];
char valset[20];

int verbose = QUIET;

int test_sysfs_node(char * sysfs)
{
#ifdef TEST_USES_STAT	
	struct stat   buffer;   
#endif

    if (verbose) {
		printf("test_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

#ifdef TEST_USES_STAT	

  return (stat (sysfs, &buffer) == 0);

#else
  
  if (access(sysfs, F_OK ) == -1)
		return(-1);
		
	return(0);
#endif

}

int read_sysfs_node(char * sysfs, char * buffer)
{
    int fd,len;
	char buf[50];
    if (verbose) {
		printf("read_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

//#ifdef USE_FCNTL
    fd = open(sysfs, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening node '%s'\n",sysfs);
        return(-1);
    }
    len = read (fd, &buf, sizeof(buf));
    close(fd);
//#else
//    FILE* f = fopen(sysfs, "w");
//    if (f == NULL) {
//        fprintf(stderr, "Error writing node '%s'\n",sysfs);
//        return(-1);
//    }
//
//    len = fread(buf,1,sizeof(buf),f);
//    fclose(f);
//#endif
	strncpy(buffer,buf,strlen(buf)-1);
	
    if (verbose) {
		printf("buf: '%s'\n",buf);
		printf("buffer: '%s'\n",buffer);
		printf("len: '%d'\n",len);
	}
    return(len);
}

int write_sysfs_node(char * sysfs, char * value)
{
    int fd;

    if (verbose) {
		printf("write_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
        printf("value: '%s'\n",value);
    }

#ifdef USE_FCNTL
    fd = open(sysfs, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(-1);
    }
    write (fd, &value, strlen(value));
    close(fd);
#else
    FILE* f = fopen(sysfs, "w");
    if (f == NULL) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(-1);
    }

    fprintf(f, "%s", value);
    fprintf(f, "\n");
    fclose(f);
#endif
    return(0);
}

int gpio_is_exported(int pin)
{
    if (verbose) {
		printf("gpio_is_exported\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d",pin);

    if (test_sysfs_node(sysfs) != 0) {
		return(-1);
	}
	return(0);
}

int gpio_export(int pin)
{
    if (verbose) {
		printf("gpio_export\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/export");
    
    sprintf(valset,"%d",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error exporting pin '%d' to node '%s/export'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_unexport(int pin)
{
    if (verbose) {
		printf("gpio_unexport\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/unexport");
    sprintf(valset,"%d",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error unexporting pin '%d' to node '%s/unexport'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_write_dir(int pin, int state)
{
    if (verbose) {
		printf("gpio_write_dir\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
	if (state == 1)
		sprintf(valset,"out");
	else
		sprintf(valset,"in");

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_write(int pin, int state)
{
    if (verbose) {
		printf("gpio_write\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);
    
    sprintf(valset,"%d",state);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    return(0);
}

int gpio_read_dir(int pin)
{
	int state,len;
    if (verbose) {
		printf("gpio_read_dir\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
   
    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"out",3) == 0)
		return(1);

    return(0);
}

int gpio_read(int pin)
{
	int state,len;
    if (verbose) {
		printf("gpio_read\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);

    if (verbose) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"1",1) == 0)
		return(1);

    return(0);
}

int get_pin_bank(int pin)
{
	int bank;
    
    if (verbose) {
		printf("get_pin_bank\n");
        printf("pin: '%d'\n",pin);
    }
	
	bank = pin/PIN_BANK_SIZE;

    if (verbose)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		exit(-1);
	}

	return(bank);
}

int get_old_pin_num(int pin)
{
	int bank,pinnum;
	
    if (verbose) {
		printf("get_old_pin_num\n");
        printf("pin: '%d'\n",pin);
    }

	bank = get_pin_bank(pin);

    if (verbose)
        printf("bank: '%d'\n",bank);
	
	pinnum = pin - (bank * PIN_BANK_SIZE);
	
    if (verbose)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		exit(-1);
	}

	return(pinnum);
}

int get_old_pin_name(int pin, char* name)
{
	int bank,pinnum;
	
    if (verbose) {
		printf("get_old_pin_name\n");
        printf("pin: '%d'\n",pin);
        printf("name: '%s'\n",name);
    }
	
	bank = get_pin_bank(pin);

    if (verbose)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		exit(-1);
	}
	
	pinnum = get_old_pin_num(pin);
	
    if (verbose)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		exit(-1);
	}

	sprintf(name,"P%d_%d",bank,pinnum);

    if (verbose) {
        printf("name: '%s'\n",name);
    }
	
	return(0);
}

int get_pin_conn(int pin)
{
	int conn;
    
//    if (verbose) {
//		printf("get_pin_conn\n");
//        printf("pin: '%d'\n",pin);
//    }
	
	switch(pin)
	{
		case 8:
		case 9:
		case 10:
		case 11:
		case 22:
		case 23:
		case 26:
		case 27:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 44:
		case 45:
		case 46:
		case 47:
		case 61:
		case 62:
		case 63:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		case 76:
		case 77:
		case 78:
		case 79:
		case 80:
		case 81:
		case 86:
		case 87:
		case 88:
		case 89:
			conn = 8;
			break;
		
		case 2:
		case 3:
		case 4:
		case 5:
		case 7:
		case 14:
		case 15:
		case 20:
		case 30:
		case 31:
		case 48:
		case 49:
		case 50:
		case 51:
		case 60:
		case 110:
		case 111:
		case 112:
		case 113:
		case 115:
		case 117:
			conn = 9;
			break;
		default:
			conn = 0;
			break;
	}
    
//    if (verbose)
//        printf("conn: '%d'\n",conn);

	return(conn);
}

int get_pin_num(int pin)
{
	int bank,pinnum;
	
//    if (verbose) {
//		printf("get_pin_num\n");
//        printf("pin: '%d'\n",pin);
//    }

	switch(pin)
	{
		case 2: pinnum = 22; break;
		case 3: pinnum = 21; break;
		case 4: pinnum = 18; break;
		case 5: pinnum = 17; break;
		case 7: pinnum = 42; break;
		case 8: pinnum = 35; break;
		case 9: pinnum = 33; break;
		case 10: pinnum = 31; break;
		case 11: pinnum = 32; break;
		case 14: pinnum = 26; break;
		case 15: pinnum = 24; break;
		case 20: pinnum = 41; break;
		case 22: pinnum = 19; break;
		case 23: pinnum = 13; break;
		case 26: pinnum = 14; break;
		case 27: pinnum = 17; break;
		case 30: pinnum = 11; break;
		case 31: pinnum = 13; break;
		case 32: pinnum = 25; break;
		case 33: pinnum = 24; break;
		case 34: pinnum = 5; break;
		case 35: pinnum = 6; break;
		case 36: pinnum = 23; break;
		case 37: pinnum = 22; break;
		case 38: pinnum = 3; break;
		case 39: pinnum = 4; break;
		case 44: pinnum = 12; break;
		case 45: pinnum = 11; break;
		case 46: pinnum = 16; break;
		case 47: pinnum = 15; break;
		case 48: pinnum = 15; break;
		case 49: pinnum = 23; break;
		case 50: pinnum = 14; break;
		case 51: pinnum = 16; break;
		case 60: pinnum = 12; break;
		case 61: pinnum = 26; break;
		case 62: pinnum = 21; break;
		case 63: pinnum = 20; break;
		case 65: pinnum = 18; break;
		case 66: pinnum = 7; break;
		case 67: pinnum = 8; break;
		case 68: pinnum = 10; break;
		case 69: pinnum = 9; break;
		case 70: pinnum = 45; break;
		case 71: pinnum = 46; break;
		case 72: pinnum = 43; break;
		case 73: pinnum = 44; break;
		case 74: pinnum = 41; break;
		case 75: pinnum = 42; break;
		case 76: pinnum = 39; break;
		case 77: pinnum = 40; break;
		case 78: pinnum = 37; break;
		case 79: pinnum = 38; break;
		case 80: pinnum = 36; break;
		case 81: pinnum = 34; break;
		case 86: pinnum = 27; break;
		case 87: pinnum = 29; break;
		case 88: pinnum = 28; break;
		case 89: pinnum = 30; break;
		case 110: pinnum = 31; break;
		case 111: pinnum = 29; break;
		case 112: pinnum = 30; break;
		case 113: pinnum = 28; break;
		case 115: pinnum = 27; break;
		case 117: pinnum = 25; break;
		default: pinnum=0; break;
	}

//    if (verbose)
//        printf("pinnum: '%d'\n",pinnum);

	return(pinnum);
}

int get_pwm_pin_name(int pin, char* name)
{
	int conn,pinnum;
	
    if (verbose) {
		printf("get_pwm_pin_name\n");
        printf("pin: '%d'\n",pin);
        //printf("name: '%s'\n",name);
    }
	
	conn = get_pin_conn(pin);

    if (verbose)
        printf("conn: '%d'\n",conn);

	if (conn < 8 || conn > 9) {
		printf("Pin # '%d' Invalid, conn '%d' out of range!\n",pin,conn);
		exit(-1);
	}
	
	pinnum = get_pin_num(pin);
	
    if (verbose)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 46) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		exit(-1);
	}

	sprintf(name,"P%d_%d",conn,pinnum);

    if (verbose) {
        printf("name: '%s'\n",name);
    }
	
	return(0);
}

int get_capemgr_num(void)
{
	int n = -1;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (verbose) {
		printf("get_capemgr_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(-1);
    }
	sprintf(tmp,"%s","bone_capemgr.");
	
	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}				
	}

	// Close the directory stream
	closedir(dp);        
	return(n);
}

int get_ocp_num(void)
{
	int n = -1;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (verbose) {
		printf("get_ocp_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(-1);
    }
	sprintf(tmp,"%s","ocp.");
	
	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}				
	}

	// Close the directory stream
	closedir(dp);        
	return(n);

}

char* get_ocp_path(void)
{

	int ocp = get_ocp_num();
	
    if (verbose) {
		printf("get_ocp_path\n");
    }

    sprintf(valset,SYSFS_OCP "%d",ocp);

    if (verbose) {
		printf("sysfs: '%s'\n",valset);
	}

	return(valset);
}

char* get_pwm_pin_path(char * pin_name)
{
    if (verbose) {
		printf("get_pwm_pin_path\n");
		printf("pin_name: '%s'\n",pin_name);
    }

	sprintf(sysfs,"%s",get_ocp_path());

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}
	
	int pin_num = get_pwm_pin_num(pin_name);
	
    if (verbose) {
		printf("pin: '%d'\n",pin_num);
	}
	
	sprintf(valset,"%s/pwm_test_%s.%d",sysfs,pin_name,pin_num);	
	
    if (verbose) {
		printf("valset: '%s'\n",valset);
	}

	return(valset);
}

int get_pwm_pin_num(char * pin_name)
{
	int n = -1;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (verbose) {
		printf("get_pwm_pin_num\n");
		printf("pin_name: '%s'\n",pin_name);
    }

//	int ocp = get_ocp_num();
	
    sprintf(sysfs,"%s",get_ocp_path());

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(-1);
    }
	sprintf(tmp,"pwm_test_%s",pin_name);
	
    if (verbose) {
		printf("tmp: '%s'\n",tmp);
	}
	
	while(NULL != (dptr = readdir(dp)) ) {
		//printf(" [%s] ",dptr->d_name);
		if (strncmp(dptr->d_name,tmp,strlen(tmp)) == 0) {
			ptr = strtok(dptr->d_name,".");
			//printf("ptr: '%s'\n",ptr);
			ptr = strtok(NULL,".");
			if (ptr != NULL)
				n = atoi(ptr);
		}				
	}

	// Close the directory stream
	closedir(dp);        
	return(n);

}

int request_pwm(int capemgrnum)
{
    if (verbose) {
		printf("request_pwm\n");
        printf("capemgrnum: '%d'\n",capemgrnum);
    }
    
    sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
	sprintf(valset,"%s","am33xx_pwm");
	
    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
        return(-1);
    }

    return(0);	
}

int request_pwm_pin(int capemgrnum, char * pwm_pin_name)
{
    if (verbose) {
		printf("request_pwm_pin\n");
        printf("capemgrnum: '%d'\n",capemgrnum);
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}
    
    sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
    sprintf(valset,"bone_pwm_%s",pwm_pin_name);

    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
        return(-1);
    }

    return(0);	
}

int pwm_write_period(char* name, long period)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (verbose) {
		printf("pwm_write_period\n");
        printf("name: '%s'\n",name);
        printf("period: '%ld'\n",period);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));
	sprintf(valset,"%ld",period);
	
    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(-1);
    }
	
    return(0);
}

int pwm_write_duty_cycle(char* name, int dutycycle)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (verbose) {
		printf("pwm_write_duty\n");
        printf("name: '%s'\n",name);
        printf("dutycycle: '%d'\n",dutycycle);
    }

	long period = pwm_read_period(name);

    if (verbose) {
		printf("period: '%ld'\n",period);
	}
	
	long duty = dutycycle * period / 100;
	
    if (verbose) {
        printf("duty: '%ld'\n",duty);
	}

	if (pwm_write_duty(name,duty) < ERROR_OK) {
        printf("Error writing duty cycle\n");
        return(-1);
    }
	
    return(0);
}

int pwm_write_duty(char* name, long duty)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (verbose) {
		printf("pwm_write_duty\n");
        printf("name: '%s'\n",name);
        printf("duty: '%ld'\n",duty);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));
	sprintf(valset,"%ld",duty);
	
    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(-1);
    }
	
    return(0);
}

long pwm_read_period(char* name)
{
	int len;
	
    if (verbose) {
		printf("pwm_read_period\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));
	
    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}
		
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}

	long period = atol(valset);

	if (verbose)
		printf("period: '%ld'\n",period);
    
    return(period);
}

long pwm_read_duty(char* name)
{
	int len;
	
    if (verbose) {
		printf("pwm_read_duty\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));
	
    if (verbose) {
		printf("sysfs: '%s'\n",sysfs);
	}
		
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(-1);
    }

    if (verbose) {
		printf("valset: '%s'\n",valset);
	}

	long duty = atol(valset);

	if (verbose)
		printf("duty: '%ld'\n",duty);
    
    return(duty);
}
