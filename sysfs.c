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

int debug = OFF;

int test_sysfs_node(char * sysfs)
{
#ifdef TEST_USES_STAT	
	struct stat   buffer;   
#endif

    if (debug) {
		printf("test_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

#ifdef TEST_USES_STAT	

  return (stat (sysfs, &buffer) == ERROR_OK);

#else
  
  if (access(sysfs, F_OK ) == ERROR)
		return(ERROR);
		
	return(ERROR_OK);
#endif

}

int read_sysfs_node(char * sysfs, char * buffer)
{
    int fd,len;
	char buf[50];
    if (debug) {
		printf("read_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
    }

//#ifdef USE_FCNTL
    fd = open(sysfs, O_RDONLY);
    if (fd < ERROR_OK) {
        fprintf(stderr, "Error opening node '%s'\n",sysfs);
        return(ERROR);
    }
    len = read (fd, &buf, sizeof(buf));
    close(fd);
//#else
//    FILE* f = fopen(sysfs, "w");
//    if (f == NULL) {
//        fprintf(stderr, "Error writing node '%s'\n",sysfs);
//        return(ERROR);
//    }
//
//    len = fread(buf,1,sizeof(buf),f);
//    fclose(f);
//#endif
	strncpy(buffer,buf,strlen(buf)-1);
	
    if (debug) {
		printf("buf: '%s'\n",buf);
		printf("buffer: '%s'\n",buffer);
		printf("len: '%d'\n",len);
	}
    return(len);
}

int write_sysfs_node(char * sysfs, char * value)
{
    int fd;

    if (debug) {
		printf("write_sysfs_node\n");
        printf("sysfs: '%s'\n",sysfs);
        printf("value: '%s'\n",value);
    }

#ifdef USE_FCNTL
    fd = open(sysfs, O_WRONLY);
    if (fd < ERROR_OK) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(ERROR);
    }
    write (fd, &value, strlen(value));
    close(fd);
#else
    FILE* f = fopen(sysfs, "w");
    if (f == NULL) {
        fprintf(stderr, "Error writing node '%s'\n",sysfs);
        return(ERROR);
    }

    fprintf(f, "%s", value);
    fprintf(f, "\n");
    fclose(f);
#endif
    return(ERROR_OK);
}

int gpio_is_exported(int pin)
{
    if (debug) {
		printf("gpio_is_exported\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d",pin);
	
    if (test_sysfs_node(sysfs) == 0) {
		return(ERROR);
	}
	return(ERROR_OK);
}

int gpio_export(int pin)
{
    if (debug) {
		printf("gpio_export\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/export");
    
    sprintf(valset,"%d",pin);

    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error exporting pin '%d' to node '%s/export'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

int gpio_unexport(int pin)
{
    if (debug) {
		printf("gpio_unexport\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/unexport");
    sprintf(valset,"%d",pin);

    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error unexporting pin '%d' to node '%s/unexport'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

int gpio_write_dir(int pin, int state)
{
    if (debug) {
		printf("gpio_write_dir\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
	if (state == 1)
		sprintf(valset,"out");
	else
		sprintf(valset,"in");

    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

int gpio_write(int pin, int state)
{
    if (debug) {
		printf("gpio_write\n");
        printf("pin: '%d'\n",pin);
        printf("state: '%d'\n",state);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);
    
    sprintf(valset,"%d",state);

    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
        printf("valset: '%s'\n",valset);
    }

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing to pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    return(ERROR_OK);
}

int gpio_read_dir(int pin)
{
	int state,len;
    if (debug) {
		printf("gpio_read_dir\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/direction",pin);
   
    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    if (debug) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"out",3) == 0)
		return(1);

    return(ERROR_OK);
}

int gpio_read(int pin)
{
	int state,len;
    if (debug) {
		printf("gpio_read\n");
        printf("pin: '%d'\n",pin);
    }

    sprintf(sysfs,SYSFS_GPIO "/gpio%d/value",pin);

    if (debug) {
        printf("sysfs: '%s'\n",sysfs);
    }
	
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading pin '%d' at node '%s'\n",pin,SYSFS_GPIO);
        return(ERROR);
    }

    if (debug) {
		printf("valset: '%s'\n",valset);
	}
	if (strncmp(valset,"1",1) == 0)
		return(1);

    return(ERROR_OK);
}

int get_pin_bank(int pin)
{
	int bank;
    
    if (debug) {
		printf("get_pin_bank\n");
        printf("pin: '%d'\n",pin);
    }
	
	bank = pin/PIN_BANK_SIZE;

    if (debug)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		return(ERROR);
	}

	return(bank);
}

int get_old_pin_num(int pin)
{
	int bank,pinnum;
	
    if (debug) {
		printf("get_old_pin_num\n");
        printf("pin: '%d'\n",pin);
    }

	bank = get_pin_bank(pin);

    if (debug)
        printf("bank: '%d'\n",bank);
	
	pinnum = pin - (bank * PIN_BANK_SIZE);
	
    if (debug)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	return(pinnum);
}

int get_old_pin_name(int pin, char* name)
{
	int bank,pinnum;
	
    if (debug) {
		printf("get_old_pin_name\n");
        printf("pin: '%d'\n",pin);
        printf("name: '%s'\n",name);
    }
	
	bank = get_pin_bank(pin);

    if (debug)
        printf("bank: '%d'\n",bank);

	if (bank < 0 || bank > 5) {
		printf("Pin # '%d' Invalid, Bank '%d' out of range!\n",pin,bank);
		return(ERROR);
	}
	
	pinnum = get_old_pin_num(pin);
	
    if (debug)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 31) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	sprintf(name,"P%d_%d",bank,pinnum);

    if (debug) {
        printf("name: '%s'\n",name);
    }
	
	return(ERROR_OK);
}

int get_pin_conn(int pin)
{
	int conn;
    
//    if (debug) {
//		printf("get_pin_conn\n");
//        printf("pin: '%d'\n",pin);
//    }

	conn = conn_map[pin];
	    
//    if (debug)
//        printf("conn: '%d'\n",conn);

	return(conn);
}

int get_pin_num(int pin)
{
	int bank,pinnum;
	
//    if (debug) {
//		printf("get_pin_num\n");
//        printf("pin: '%d'\n",pin);
//    }

	pinnum = pin_map[pin];

//    if (debug)
//        printf("pinnum: '%d'\n",pinnum);

	return(pinnum);
}

int get_pwm_pin_name(int pin, char* name)
{
	int conn,pinnum;
	
    if (debug) {
		printf("get_pwm_pin_name\n");
        printf("pin: '%d'\n",pin);
        //printf("name: '%s'\n",name);
    }
	
	conn = get_pin_conn(pin);

    if (debug)
        printf("conn: '%d'\n",conn);

	if (conn < 8 || conn > 9) {
		printf("Pin # '%d' Invalid, conn '%d' out of range!\n",pin,conn);
		return(ERROR);
	}
	
	pinnum = get_pin_num(pin);
	
    if (debug)
        printf("pinnum: '%d'\n",pinnum);

	if (pinnum < 0 || pinnum > 46) {
		printf("Pin # '%d' Invalid, pinnum '%d' out of range!\n",pin,pinnum);
		return(ERROR);
	}

	sprintf(name,"P%d_%d",conn,pinnum);

    if (debug) {
        printf("name: '%s'\n",name);
    }
	
	return(ERROR_OK);
}

int get_capemgr_num(void)
{
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (debug) {
		printf("get_capemgr_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
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
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (debug) {
		printf("get_ocp_num\n");
    }

    sprintf(sysfs,SYSFS_DEV);

    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
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
	
    if (debug) {
		printf("get_ocp_path\n");
    }

    sprintf(valset,SYSFS_OCP "%d",ocp);

    if (debug) {
		printf("sysfs: '%s'\n",valset);
	}

	return(valset);
}

char* get_pwm_pin_path(char * pin_name)
{
    if (debug) {
		printf("get_pwm_pin_path\n");
		printf("pin_name: '%s'\n",pin_name);
    }

	sprintf(sysfs,"%s",get_ocp_path());

    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}
	
	int pin_num = get_pwm_pin_num(pin_name);
	
    if (debug) {
		printf("pin: '%d'\n",pin_num);
	}
	
	sprintf(valset,"%s/pwm_test_%s.%d",sysfs,pin_name,pin_num);	
	
    if (debug) {
		printf("valset: '%s'\n",valset);
	}

	return(valset);
}

int get_pwm_pin_num(char * pin_name)
{
	int n = ERROR;
	DIR *dp = NULL;
	char tmp[20];
	char * ptr;
	struct dirent *dptr = NULL;
	
    if (debug) {
		printf("get_pwm_pin_num\n");
		printf("pin_name: '%s'\n",pin_name);
    }

//	int ocp = get_ocp_num();
	
    sprintf(sysfs,"%s",get_ocp_path());

    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}

	if ((dp = opendir(sysfs)) == NULL) {
        printf("Error opening sysfs node '%s'\n",sysfs);
        return(ERROR);
    }
	sprintf(tmp,"pwm_test_%s",pin_name);
	
    if (debug) {
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
    if (debug) {
		printf("request_pwm\n");
        printf("capemgrnum: '%d'\n",capemgrnum);
    }
    
    sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
	sprintf(valset,"%s","am33xx_pwm");
	
    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}

    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
        return(ERROR);
    }

    return(ERROR_OK);	
}

int request_pwm_pin(int capemgrnum, char * pwm_pin_name)
{
    if (debug) {
		printf("request_pwm_pin\n");
        printf("capemgrnum: '%d'\n",capemgrnum);
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	if (get_pwm_pin_num(pwm_pin_name) >= ERROR_OK) {
		if (debug)
			printf("PWM Pin is already currently active!\n");
		return(ERROR_OK);
	}
    
	if (debug)
		printf("PWM Pin is not currently active, requesting!\n");

	sprintf(sysfs,SYSFS_CAPE "%d/slots",capemgrnum);
	sprintf(valset,"bone_pwm_%s",pwm_pin_name);

	if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);	
}

int pwm_pin_run(char * pwm_pin_name)
{
    if (debug) {
		printf("pwm_pin_run\n");
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	if (get_pwm_pin_num(pwm_pin_name) < ERROR_OK) {
//		if (debug)
			printf("PWM Pin is NOT already currently active!\n");
		return(ERROR);
	}
    
	if (debug)
		printf("PWM Pin is currently active!\n");

	sprintf(sysfs,"%s",get_pwm_pin_path(pwm_pin_name));
	sprintf(valset,"%d",1);

	if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);	
}

int pwm_pin_stop(char * pwm_pin_name)
{
    if (debug) {
		printf("pwm_pin_stop\n");
        printf("pwm_pin_name: '%s'\n",pwm_pin_name);
	}

	if (get_pwm_pin_num(pwm_pin_name) < ERROR_OK) {
//		if (debug)
			printf("PWM Pin is NOT already currently active!\n");
		return(ERROR);
	}
    
	if (debug)
		printf("PWM Pin is currently active!\n");

	sprintf(sysfs,"%s",get_pwm_pin_path(pwm_pin_name));
	sprintf(valset,"%d",0);

	if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
	if (write_sysfs_node(sysfs, valset) < 0) {
		printf("Error requesting '%s' at node '%s'\n",valset,sysfs);
		return(ERROR);
	}

    return(ERROR_OK);	
}

int pwm_write_period(char* name, long period)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (debug) {
		printf("pwm_write_period\n");
        printf("name: '%s'\n",name);
        printf("period: '%ld'\n",period);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));
	sprintf(valset,"%ld",period);
	
    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(ERROR);
    }
	
    return(ERROR_OK);
}

int pwm_write_duty(char* name, long duty)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
    if (debug) {
		printf("pwm_write_duty\n");
        printf("name: '%s'\n",name);
        printf("duty: '%ld'\n",duty);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));
	sprintf(valset,"%ld",duty);
	
    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
		printf("valset: '%s'\n",valset);
	}
	
    if (write_sysfs_node(sysfs, valset) < 0) {
        printf("Error writing '%s' to node '%s'\n",valset,sysfs);
        return(ERROR);
    }
	
    return(ERROR_OK);
}

int pwm_write_duty_cycle(char* name, int dutycycle)
{
	// OCP/pwm_test_PINNAME.pin
	//echo ${DUTY} > ${PWM}/duty
	
    if (debug) {
		printf("pwm_write_duty\n");
        printf("name: '%s'\n",name);
        printf("dutycycle: '%d'\n",dutycycle);
    }

	long period = pwm_read_period(name);

    if (debug) {
		printf("period: '%ld'\n",period);
	}
	
	long duty = dutycycle * period / 100;
	
	duty = period - duty;
	
    if (debug) {
        printf("duty: '%ld'\n",duty);
	}

	if (pwm_write_duty(name,duty) < ERROR_OK) {
        printf("Error writing duty cycle\n");
        return(ERROR);
    }
	
    return(ERROR_OK);
}

long pwm_read_period(char* name)
{
	int len;
	
    if (debug) {
		printf("pwm_read_period\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/period",get_pwm_pin_path(name));
	
    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}
		
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(ERROR);
    }

    if (debug) {
		printf("valset: '%s'\n",valset);
	}

	long period = atol(valset);

	if (debug)
		printf("period: '%ld'\n",period);
    
    return(period);
}

long pwm_read_duty(char* name)
{
	int len;
	
    if (debug) {
		printf("pwm_read_duty\n");
        printf("name: '%s'\n",name);
    }

	sprintf(sysfs,"%s/duty",get_pwm_pin_path(name));
	
    if (debug) {
		printf("sysfs: '%s'\n",sysfs);
	}
		
	memset(valset,0x00,sizeof(valset));
	
    if ((len = read_sysfs_node(sysfs, valset)) < 0) {
        printf("Error reading node '%s'\n",sysfs);
        return(ERROR);
    }

    if (debug) {
		printf("valset: '%s'\n",valset);
	}

	long duty = atol(valset);

	if (debug)
		printf("duty: '%ld'\n",duty);
    
    return(duty);
}
