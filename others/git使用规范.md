git使用规范

<!--more-->

在软件开发过程中，规范的分支管理能够有效提高团队协作和项目稳定性。下面是一种常见的分支管理策略——Git Flow，适用于大多数项目的版本管理。具体步骤如下：

### Git Flow 分支管理模型

#### 1. 主分支（Main or Master）
主要分支用于保存发布的正式版本。任何提交到主分支的代码都应该是稳定且准备发布的代码。

#### 2. 开发分支（Develop）
开发分支是所有开发动作的基础分支。这个分支包含最新的开发代码，能够稳定运行但可能未经过全面测试。

#### 3. 功能分支（Feature Branches）
这些分支用于开发新功能，每个新功能创建一个独立的功能分支。这些分支从开发分支中派生，完成后合并回开发分支。

* **命名规范**： feature/功能名称
* **创建**：从开发分支创建 `git checkout -b feature/功能名称 develop`
* **合并回开发分支**：功能完成后合并回开发分支 `git checkout develop` 然后 `git merge --no-ff feature/功能名称`
* **删除**：合并完成后删除 `git branch -d feature/功能名称`

#### 4. 发布分支（Release Branches）
当准备发布一个新的版本时，从开发分支创建一个发布分支。这些分支用于修正Bug和准备发布，包括更新版本号、文档等。完成后合并到主分支和开发分支。

* **命名规范**： release/版本号
* **创建**：从开发分支创建 `git checkout -b release/版本号 develop`
* **合并到主分支**：发布完成并合并到主分支 `git checkout main` 然后 `git merge --no-ff release/版本号`
* **合并回开发分支**：然后将这些改动合并回开发分支 `git checkout develop` 然后 `git merge --no-ff release/版本号`
* **删除**：合并完成后删除 `git branch -d release/版本号`

#### 5. 热修复分支（Hotfix Branches）
这些分支用于修复生产环境中的紧急问题。它们直接从主分支创建，修复完成后合并回主分支和开发分支。

* **命名规范**： hotfix/修复描述
* **创建**：从主分支创建 `git checkout -b hotfix/修复描述 main`
* **合并到主分支**：修复完成并合并到主分支 `git checkout main` 然后 `git merge --no-ff hotfix/修复描述`
* **合并回开发分支**：然后将这些改动合并回开发分支 `git checkout develop` 然后 `git merge --no-ff hotfix/修复描述`
* **删除**：合并完成后删除 `git branch -d hotfix/修复描述`

### 示例工作流程

1. **创建开发分支**：
   ```sh
   git checkout -b develop main
   ```

2. **创建功能分支进行开发**：
   ```sh
   git checkout -b feature/add-new-feature develop
   [进行开发...]
   git checkout develop
   git merge --no-ff feature/add-new-feature
   git branch -d feature/add-new-feature
   ```

3. **准备发布**：
   ```sh
   git checkout -b release/v1.0 develop
   [修正Bug，准备发布...]
   git checkout main
   git merge --no-ff release/v1.0
   git checkout develop
   git merge --no-ff release/v1.0
   git branch -d release/v1.0
   ```

4. **紧急修复**：
   ```sh
   git checkout -b hotfix/fix-critical-bug main
   [进行修复...]
   git checkout main
   git merge --no-ff hotfix/fix-critical-bug
   git checkout develop
   git merge --no-ff hotfix/fix-critical-bug
   git branch -d hotfix/fix-critical-bug
   ```

通过使用Git Flow模型，你可以清晰地管理不同类型的工作并确保代码质量，减少合并冲突，同时保证主分支的稳定。 


---

功能分支（Feature Branch）命名一般遵循一定的规范，从名称中可以清楚地知道该分支的目的或正在进行的功能。常见的命名惯例是在分支名称前加上「feature/」，后接简要描述功能的关键词或JIRA号、任务编号等。下面是一些具体示例：

1. **基于功能描述**：
   - `feature/user-login`
   - `feature/payment-integration`
   - `feature/update-profile-page`
   - `feature/shopping-cart`

2. **基于任务编号或JIRA号**：
   - `feature/JIRA-1234-user-login`
   - `feature/issue-5678-payment-integration`

3. **结合功能描述和任务编号**：
   - `feature/JIRA-2345-update-profile-page`
   - `feature/TASK-7890-shopping-cart`

### 示例说明

1. **`feature/user-login`**：
   - 这个分支名称清晰地表明该分支用于开发“用户登录”功能。任何需要实现用户登录功能的代码更改都在该分支中进行。

2. **`feature/payment-integration`**：
   - 该分支用于支付集成功能的开发，包括与第三方支付服务的对接、支付流程的实现等。

3. **`feature/JIRA-1234-user-login`**：
   - 这里的分支名称结合了JIRA任务号和功能描述，便于追踪任务进度和了解分支的目标。

4. **`feature/issue-5678-payment-integration`**：
   - 该分支创建用于处理编号为5678的任务，目标是实现支付集成功能。

5. **`feature/JIRA-2345-update-profile-page`**：
   - 分支名称表明它与JIRA上编号为2345的任务相关，主要用于用户个人资料页面的更新功能开发。

### 举例的实际操作

假设项目开发中新添加用户登录功能，开发人员Alice收到任务并创建功能分支：

```sh
# 从develop分支创建功能分支
git checkout -b feature/user-login develop

# Alice在feature/user-login中进行开发
[开发用户登录功能...]

# 将功能开发完成后合并回开发分支
git checkout develop
git merge --no-ff feature/user-login

# 删除功能分支
git branch -d feature/user-login
```

通过遵循这样的分支命名和使用规范，团队成员可以轻松地识别每个分支的用途，方便协作和代码管理。 

---


合并分支时，不同的策略可以影响代码库的历史记录、可读性以及维护性。常用的合并策略包括创建合并提交（merge commit）、压缩合并（squash and merge）和变基（rebase）。下面分别介绍它们的特点及使用场景。

### 创建合并提交（Merge Commit）

#### 特点
- **保留所有历史记录**：原分支的所有提交记录都保留，且生成一个新的合并提交。
- **显示分支结构**：可以直观查看分支合并情况、来源以及合并点。

#### 适用场景
- **团队协作**：需要保留详细的开发历史，以便追踪每次更改的详细过程。
- **复杂项目**：多分支并行开发，清楚显示合并结构有助于理解完整的开发流程。

#### 操作
```sh
git checkout target-branch
git merge source-branch
```

### 压缩合并（Squash and Merge）

#### 特点
- **简化历史记录**：将源分支的所有提交压缩成一个提交，合并到目标分支。
- **减少噪音**：适用于源分支中有很多小而琐碎的提交，需要简化提交历史。

#### 适用场景
- **单个功能**：功能分支包含很多中间提交（例如小修复、调试输出等），希望在目标分支中只保留一个清晰的功能完成记录。
- **代码审查后**：代码审查过程中产生了多个小提交，最终合并希望保留简洁、易读的历史记录。

#### 操作
通过GitHub或GitLab等平台的Web UI操作，通常有一个 `Squash and Merge` 选项，或者在命令行中：

```sh
git checkout target-branch
git merge --squash source-branch
git commit -m "合并源分支并压缩：source-branch"
```

### 变基（Rebase）

#### 特点
- **重写历史**：将源分支的提交重新应用在目标分支基础上，形成线性的提交历史。
- **干净历史**：避免了合并提交，使得提交历史更加线性和直观。

#### 适用场景
- **个人项目**：你是唯一的开发者或有极少数人参与，重写历史的风险低。
- **代码整理**：希望在合并前整理和清理提交历史，形成干净的线性提交史。

#### 注意事项
- **禁止在公共分支上变基**：非必要时，避免在已推送和多人协作的公共分支上使用变基，否则会导致其他人仓库的历史记录冲突。

#### 操作
```sh
# 切到源分支进行变基
git checkout source-branch
git rebase target-branch

# 解决冲突后，继续变基
git rebase --continue

# 切回目标分支并快速前推（保证目标分支是最新的）
git checkout target-branch
git merge source-branch
```

### 总结
- **创建合并提交**：适用于需要保留完整详细的历史记录，适合团队协作、复杂项目。
- **压缩合并**：适用于简化历史记录，功能开发中产生了很多中间提交的情况。
- **变基**：适用于整理提交史，形成线性历史，但要谨慎使用，不要在公共分支上重写历史。

选择哪种合并策略，需根据项目的具体需求和团队协作方式综合考虑。 