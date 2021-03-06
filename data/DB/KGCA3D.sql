USE [master]
GO
/****** Object:  Database [KGCA3D]    Script Date: 2019-07-26 오후 4:13:07 ******/
CREATE DATABASE [KGCA3D]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'KGCA3D', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL13.MSSQLSERVER\MSSQL\DATA\KGCA3D.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'KGCA3D_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL13.MSSQLSERVER\MSSQL\DATA\KGCA3D_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
ALTER DATABASE [KGCA3D] SET COMPATIBILITY_LEVEL = 100
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [KGCA3D].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [KGCA3D] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [KGCA3D] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [KGCA3D] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [KGCA3D] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [KGCA3D] SET ARITHABORT OFF 
GO
ALTER DATABASE [KGCA3D] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [KGCA3D] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [KGCA3D] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [KGCA3D] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [KGCA3D] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [KGCA3D] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [KGCA3D] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [KGCA3D] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [KGCA3D] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [KGCA3D] SET  DISABLE_BROKER 
GO
ALTER DATABASE [KGCA3D] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [KGCA3D] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [KGCA3D] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [KGCA3D] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [KGCA3D] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [KGCA3D] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [KGCA3D] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [KGCA3D] SET RECOVERY FULL 
GO
ALTER DATABASE [KGCA3D] SET  MULTI_USER 
GO
ALTER DATABASE [KGCA3D] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [KGCA3D] SET DB_CHAINING OFF 
GO
ALTER DATABASE [KGCA3D] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [KGCA3D] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [KGCA3D] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [KGCA3D] SET QUERY_STORE = OFF
GO
USE [KGCA3D]
GO
ALTER DATABASE SCOPED CONFIGURATION SET LEGACY_CARDINALITY_ESTIMATION = OFF;
GO
ALTER DATABASE SCOPED CONFIGURATION SET MAXDOP = 0;
GO
ALTER DATABASE SCOPED CONFIGURATION SET PARAMETER_SNIFFING = ON;
GO
ALTER DATABASE SCOPED CONFIGURATION SET QUERY_OPTIMIZER_HOTFIXES = OFF;
GO
USE [KGCA3D]
GO
/****** Object:  Table [dbo].[Account]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Account](
	[USERID] [nchar](10) NOT NULL,
	[USERPS] [nchar](10) NOT NULL,
	[ACCOUNTTIME] [smalldatetime] NOT NULL,
	[Login] [smalldatetime] NULL,
	[Logout] [smalldatetime] NULL,
 CONSTRAINT [PK_Account] PRIMARY KEY CLUSTERED 
(
	[USERID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[USERLIST]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[USERLIST](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[USERID] [nchar](10) NOT NULL,
	[USERPS] [nchar](10) NOT NULL,
	[AccountTime] [datetime] NULL,
	[LoginTime] [datetime] NULL,
	[LogoutTime] [datetime] NULL,
	[BlobData] [varbinary](max) NULL,
 CONSTRAINT [PK_USERLIST] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
ALTER TABLE [dbo].[Account] ADD  DEFAULT (getdate()) FOR [ACCOUNTTIME]
GO
ALTER TABLE [dbo].[USERLIST] ADD  CONSTRAINT [DF_USERLIST_AccountTime]  DEFAULT (getdate()) FOR [AccountTime]
GO
/****** Object:  StoredProcedure [dbo].[AccountCreate]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- 계정 생성 성공 : 0
-- 중복 경우 : 1
-- 이외 경우 : 2
-- =============================================
CREATE PROCEDURE [dbo].[AccountCreate]	
	@UID NCHAR(10),
	@UPS NCHAR(10)
AS
	SET NOCOUNT ON
	BEGIN TRY
		BEGIN TRAN
			INSERT INTO Account(USERID, USERPS, ACCOUNTTIME)
			VALUES( @UID, @UPS, default );

			EXECUTE KGCA3D.dbo.LoginUser @UID, @UPS
		COMMIT TRAN
		RETURN 0;
	END TRY

	BEGIN CATCH
		ROLLBACK
		DECLARE @ret NCHAR(10)
		SELECT @ret = USERID
		FROM Account
		WHERE USERID = @UID
		-- 이미 존재하는 ID-> 1
		IF(@ret <>  N'')
			BEGIN
				RETURN 1;
			END
		RETURN 2;
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[CreateAccountUser]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[CreateAccountUser]
			@UID NCHAR(10), 
			@UPS NCHAR(10),
			@RETN int OUTPUT
AS
	SET NOCOUNT ON
	BEGIN TRY
		DECLARE @ret NCHAR(10);
		
		select @ret=USERID from USERLIST 
		where USERID= @UID

		IF( @ret <> N'' )
		BEGIN
			SET @RETN = 3
			RETURN 3;
		END

		INSERT INTO USERLIST(USERID, USERPS, AccountTime)  
		VALUES(@UID, @UPS, GETDATE());
		EXECUTE KGCA3D.dbo.JoinUser @UID, @UPS
		SET @RETN = 1
		RETURN 1;
	END TRY
	-- ERROR
	BEGIN CATCH
		SET @RETN = 9
		return 9; 
	END CATCH
GO
/****** Object:  StoredProcedure [dbo].[GetImageStreaming]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetImageStreaming]
	@Param1 NCHAR(10),
	@Param2 VARBINARY(MAX) OUTPUT
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	SELECT @Param2 = BlobData FROM USERLIST WHERE USERID = @Param1
END

GO
/****** Object:  StoredProcedure [dbo].[JoinUser]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[JoinUser]	
	@UID NCHAR(10),
	@UPS NCHAR(10)
AS
UPDATE KGCA3D.dbo.USERLIST
	SET LoginTime = GETDATE()
	WHERE USERID = @UID
RETURN 3;
GO
/****** Object:  StoredProcedure [dbo].[LoginUser]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[LoginUser]	
	@UID NCHAR(10),
	@UPS NCHAR(10)
AS
UPDATE KGCA3D.dbo.Account
	SET Login = GETDATE()
	WHERE USERID = @UID
RETURN 3;
GO
/****** Object:  StoredProcedure [dbo].[LogoutUser]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[LogoutUser]	
	@UID NCHAR(10),
	@UPS NCHAR(10)
AS
UPDATE KGCA3D.dbo.Account
	SET Logout = GETDATE()
	WHERE USERID = @UID
RETURN 3;
GO
/****** Object:  StoredProcedure [dbo].[UpdateSetUser]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[UpdateSetUser]
	@param1 NCHAR(10),
	@param2 NCHAR(10),
	@param3 NCHAR(10)
AS
	UPDATE USERLIST SET 
	USERID=@param1, USERPS=@param2
	WHERE USERID=@param3
RETURN 0
GO
/****** Object:  StoredProcedure [dbo].[usp_pass]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[usp_pass]	
	@UID NCHAR(10)
	
AS
BEGIN
	SELECT * FROM dbo.USERLIST
	WHERE @UID=USERID;
END
RETURN 3;
GO
/****** Object:  StoredProcedure [dbo].[usp_passout]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[usp_passout]	
	@UID NCHAR(10),
	@UPS NCHAR(10) OUTPUT	
AS
BEGIN
	SELECT @UPS=USERPS FROM dbo.USERLIST
	WHERE @UID=USERID;
END
RETURN 1;
GO
/****** Object:  StoredProcedure [dbo].[usp_userinfo]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[usp_userinfo]	
	@UID NCHAR(10)
	
AS
BEGIN
	SELECT * FROM dbo.Account
	WHERE @UID=USERID;
END
RETURN 3;
GO
/****** Object:  StoredProcedure [dbo].[uspAllUserList]    Script Date: 2019-07-26 오후 4:13:07 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[uspAllUserList]
AS
	SELECT * FROM dbo.USERLIST;
GO
USE [master]
GO
ALTER DATABASE [KGCA3D] SET  READ_WRITE 
GO
