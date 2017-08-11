#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#
Summary:   Brother sane backend Driver
Vendor:    Brother Industries, Ltd.
Name:      brscan
Version:   0.2.4
Release:   4
License:   2003 Brother Industries, Ltd. All Rights Reserved
Group:     Applications
Packager:  norbert.eicker@gmx.de
Source0:   brscan-0.2.4.tar.gz
BuildRequires:	sane-backends-devel libusb-1_0-devel

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

%description
Brother sane backend Driver

%prep
%setup -q -n %{name}-%{version}

%build

%configure
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
make DESTDIR=%{buildroot} install

%clean
rm -rf %{buildroot}

%post
if [ $1 -eq 1 ] ; then
    # first install
    %{_libexecdir}/brscan/setupSaneScan -i
fi
exit 0

%preun
if [ $1 -eq 0 ] ; then
    # final de-install
    %{_libexecdir}/brscan/setupSaneScan -e
fi
exit 0

%files
%defattr(-,root,root)
%{_bindir}/brsaneconfig
%{_libdir}/libbrcolm.so.1.0.1
%{_libdir}/libbrcolm.so.1
%{_libdir}/libbrscandec.so.1.0.0
%{_libdir}/libbrscandec.so.1
%{_libdir}/sane/libsane-brother.so.1.0.7
%{_libdir}/sane/libsane-brother.so.1
%exclude %{_libdir}/sane/libsane-brother.la
%exclude %{_libdir}/sane/libsane-brother.so
%{_libexecdir}/brscan
%{_datadir}/sane/brother
