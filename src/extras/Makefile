#
# $Id: Makefile,v 1.14 2012/11/27 00:48:35 phil Exp $
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
# Revision 1.14  2012/11/27 00:48:35  phil
# Copyright Storm for Emerald Boa
#
# Revision 1.13  2012/05/06 05:48:42  phil
# Copyright Storm for Mamba
#
# Revision 1.12  2012/01/23 20:00:27  phil
# caching named package changed from 5 to 6. Do we really need this anymore?
#
# Revision 1.11  2011/07/23 02:30:44  phil
# Viper Copyright
#
# Revision 1.10  2010/09/07 23:53:05  bruno
# star power for gb
#
# Revision 1.9  2010/06/22 21:26:22  mjk
# Build env is now from src/devel package, nothing outside of base roll.
#
# Revision 1.8  2009/05/01 19:07:05  mjk
# chimi con queso
#
# Revision 1.7  2008/10/18 00:55:59  mjk
# copyright 5.1
#
# Revision 1.6  2008/07/29 20:46:44  bruno
# build fix
#
# Revision 1.5  2008/05/23 18:59:31  anoop
# Small changes to the base roll to make a cleaner build
#
# Revision 1.4  2008/03/06 23:41:41  mjk
# copyright storm on
#
# Revision 1.3  2007/06/23 04:03:22  mjk
# mars hill copyright
#
# Revision 1.2  2006/12/02 01:04:53  anoop
# Ridiculously big ass commit.
# Also known as the week after thanksgiving 2006. Or "The day Anoop
# broke Rocks".
#
# Main Changes.
#
# 1. Added a roll-profile.mk file. This is meant as a makefile for building
# the profile rpm containing all the XML files meant for the roll. This is a
# breakaway from the spec.in file method of building the profile RPM.
#
# 2. The variable PWD is now changed to CURDIR. The main reason for this is
# PWD is supplied by the shell. CURDIR is the variable supplied by gmake itself.
# This means we can have a slightly more platform independant way of doing things.
# Also Solaris was failing to set PWD correctly in the source directories, wreaking
# havoc on the location of the BUILD and PKG directories.
#
# Revision 1.1  2006/09/15 04:55:28  bruno
# make sure caching-nameserver is present in the distro
#

REDHAT.ROOT     = $(CURDIR)/../../
-include $(ROCKSROOT)/etc/Rules.mk
include Rules.mk


rpm::
	rocks create distro 
	mkdir -p $(REDHAT.RPMS)/$(ARCH)
	cp $(DISTPATH)/$(CACHENAMED)*rpm $(REDHAT.RPMS)/$(ARCH)
	touch -t 197012310000 $(REDHAT.RPMS)/$(ARCH)/$(CACHENAMED)*rpm
	chmod 644 $(REDHAT.RPMS)/$(ARCH)/$(CACHENAMED)*rpm


clean::
	rm -rf rocks-dist
	rm -rf cachedir

