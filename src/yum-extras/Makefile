# --------------------------------------------------- -*- Makefile -*- --
# $Id: Makefile,v 1.3 2012/11/27 00:48:51 phil Exp $
#
# @Copyright@
# 
# 				Rocks(r)
# 		         www.rocksclusters.org
# 		         version 6.2 (SideWinder)
# 		         version 7.0 (Manzanita)
# 
# Copyright (c) 2000 - 2017 The Regents of the University of California.
# All rights reserved.	
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
# 
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright
# notice unmodified and in its entirety, this list of conditions and the
# following disclaimer in the documentation and/or other materials provided 
# with the distribution.
# 
# 3. All advertising and press materials, printed or electronic, mentioning
# features or use of this software must display the following acknowledgement: 
# 
# 	"This product includes software developed by the Rocks(r)
# 	Cluster Group at the San Diego Supercomputer Center at the
# 	University of California, San Diego and its contributors."
# 
# 4. Except as permitted for the purposes of acknowledgment in paragraph 3,
# neither the name or logo of this software nor the names of its
# authors may be used to endorse or promote products derived from this
# software without specific prior written permission.  The name of the
# software includes the following terms, and any derivatives thereof:
# "Rocks", "Rocks Clusters", and "Avalanche Installer".  For licensing of 
# the associated name, interested parties should contact Technology 
# Transfer & Intellectual Property Services, University of California, 
# San Diego, 9500 Gilman Drive, Mail Code 0910, La Jolla, CA 92093-0910, 
# Ph: (858) 534-5815, FAX: (858) 534-7345, E-MAIL:invent@ucsd.edu
# 
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS''
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
# IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# @Copyright@
#
# $Log: Makefile,v $
# Revision 1.3  2012/11/27 00:48:51  phil
# Copyright Storm for Emerald Boa
#
# Revision 1.2  2012/05/06 05:48:50  phil
# Copyright Storm for Mamba
#
# Revision 1.1  2012/03/26 17:49:03  phil
# Alternative Repos Requested. 	Disabled in rocks-post
#
#

REDHAT.ROOT     = $(CURDIR)/../../
HTTPGET         = $(ROCKSROOT)/bin/httpget.sh
MAKE.iscontrib	= 1

-include $(ROCKSROOT)/etc/Rules.mk
include Rules.mk

-include $(ROCKSROOT)/etc/python.mk
include python.mk

#find the epel_rpm inside the list of rpm
EPEL_RPM = $(shell for i in $(REPORPMS.NOARCH);do echo $$i | grep epel; done)
#evaluate to true if it is installed when this script runs
IS_EPEL_INSTALLED = $(shell rpm -qa |grep epel)

# ROCKS8: yumdownloader replaced by dnf download.
# https://fedoraproject.org/wiki/Yum_to_DNF_Cheatsheet

rpm::	build
	# you are wondering why this mess?
	# if we are builing on a bare Rocky we need to install epel to download
	# fail2ban but then we have to remove it
	# if we are on a Rocks node we don't need to install it
	test "$(IS_EPEL_INSTALLED)" || rpm -Uvh $(EPEL_RPM);
	dnf download --enablerepo=epel --destdir=$(REDHAT.RPMS)/noarch $(FAIL2BAN.PKGS);
	test "$(IS_EPEL_INSTALLED)" || rpm -ev $(EPEL_RPM:.rpm=);
ifdef REPORPMS
	-cp $(REPORPMS) $(REDHAT.RPMS)/$(ARCH)/
endif
ifdef REPORPMS.NOARCH
	-cp $(REPORPMS.NOARCH) $(REDHAT.RPMS)/noarch/
endif
	-chmod go+r $(REDHAT.RPMS)/noarch/*rpm
	-chmod go+r $(REDHAT.RPMS)/$(ARCH)/*rpm
build:
# ROCKS8
# https://mirrors.xtom.de/epel/8/Everything/x86_64/Packages/e/epel-release-8-19.el8.noarch.rpm
ifeq ($(shell ! test -f epel-release-8-19.el8.noarch.rpm && echo -n yes),yes)
	@echo "ROCKS8: Sideloading epel-release-8-19.el8.noarch.rpm."
	$(HTTPGET) -B https://dl.fedoraproject.org -F pub/epel/8/Everything/x86_64/Packages/e -n epel-release-8-19.el8.noarch.rpm
endif
	mkdir -p $(REDHAT.RPMS)/$(ARCH)/
	mkdir -p $(REDHAT.RPMS)/noarch/
