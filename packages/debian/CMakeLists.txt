SET(INSTALL_DIR /etc/remoteadmin)

# Get architecture
EXECUTE_PROCESS(COMMAND dpkg --print-architecture
                OUTPUT_VARIABLE arch
                OUTPUT_STRIP_TRAILING_WHITESPACE)

SET(DATA ${PROJECT_FOLDER}/packages/debian/data)

INSTALL(TARGETS MainPage DESTINATION /usr/sbin)
INSTALL(DIRECTORY ${PROJECT_FOLDER}/css DESTINATION /usr/share/remoteadmin)

INSTALL(FILES ${DATA}/vsftpd.conf DESTINATION /etc)
INSTALL(FILES ${DATA}/vsftpd DESTINATION /etc/pam.d)
INSTALL(FILES ${DATA}/ftpuser.conf.default DESTINATION /usr/share/remoteadmin)


SET(CPACK_GENERATOR "DEB")
SET(CPACK_SOURCE_GENERATOR "DEB")
SET(CPACK_PACKAGE_VERSION "0.0.2")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jose Luis Lafuente")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${arch}")
SET(CPACK_DEBIAN_PACKAGE_SECTION "utils")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "bindfs, vsftpd, autofs, witty(>=3.1.10), libdb4.8++, adduser")

SET(CONTROL ${PROJECT_FOLDER}/packages/debian/control)
SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CONTROL}/postinst;${CONTROL}/conffiles;" )


INCLUDE(CPack)

 