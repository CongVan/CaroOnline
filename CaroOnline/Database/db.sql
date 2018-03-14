USE [master]
GO
/****** Object:  Database [CaroOnlineDB]    Script Date: 14/03/2018 9:10:45 CH ******/
CREATE DATABASE [CaroOnlineDB]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'CaroOnlineDB', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\CaroOnlineDB.mdf' , SIZE = 3264KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'CaroOnlineDB_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL12.MSSQLSERVER\MSSQL\DATA\CaroOnlineDB_log.ldf' , SIZE = 816KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [CaroOnlineDB] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [CaroOnlineDB].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [CaroOnlineDB] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET ARITHABORT OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [CaroOnlineDB] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [CaroOnlineDB] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET  ENABLE_BROKER 
GO
ALTER DATABASE [CaroOnlineDB] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [CaroOnlineDB] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET RECOVERY FULL 
GO
ALTER DATABASE [CaroOnlineDB] SET  MULTI_USER 
GO
ALTER DATABASE [CaroOnlineDB] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [CaroOnlineDB] SET DB_CHAINING OFF 
GO
ALTER DATABASE [CaroOnlineDB] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [CaroOnlineDB] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
ALTER DATABASE [CaroOnlineDB] SET DELAYED_DURABILITY = DISABLED 
GO
USE [CaroOnlineDB]
GO
/****** Object:  Table [dbo].[Games]    Script Date: 14/03/2018 9:10:45 CH ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Games](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[UserId1] [int] NULL,
	[UserId2] [int] NULL,
	[DateGame] [datetime] NULL,
	[Winer] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Users]    Script Date: 14/03/2018 9:10:45 CH ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Users](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](100) NULL,
	[Email] [varchar](100) NULL,
	[Pass] [varchar](255) NULL,
PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
SET IDENTITY_INSERT [dbo].[Users] ON 

INSERT [dbo].[Users] ([ID], [Name], [Email], [Pass]) VALUES (2, N'123', N'123@gmail.com', N'123')
INSERT [dbo].[Users] ([ID], [Name], [Email], [Pass]) VALUES (3, N'User1', N'123@gmail.com', N'123')
INSERT [dbo].[Users] ([ID], [Name], [Email], [Pass]) VALUES (4, N'User2', N'123@gmail.com', N'123')
INSERT [dbo].[Users] ([ID], [Name], [Email], [Pass]) VALUES (5, N'User3', N'123@gmail.com', N'123')
INSERT [dbo].[Users] ([ID], [Name], [Email], [Pass]) VALUES (6, N'User4', N'123@gmail.com', N'123')
SET IDENTITY_INSERT [dbo].[Users] OFF
USE [master]
GO
ALTER DATABASE [CaroOnlineDB] SET  READ_WRITE 
GO
