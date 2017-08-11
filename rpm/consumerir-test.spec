Name: consumerir-test
Version: 0.0.1
Release: 1
Summary: Testing consumer IR on android devices
Group: System/Network
License: LGPLv2.1
URL: https://example.com
Source0: %{name}-%{version}.tar.bz2
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(android-headers)
BuildRequires:  pkgconfig(libhardware)
BuildRequires:  pkgconfig(libvibrator)
BuildRequires:  libprofile-qt5-devel

%description
%{summary}.

%files
%defattr(-,root,root,-)
%{_bindir}/consumerir-test

%prep
%setup -q -n %{name}-%{version}

%build
%qmake5
make

%install
%qmake5_install

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig
