#include "TitleScene.h"
#include "ObjectCommon.h"
#include "SpriteCommon.h"
#include "SceneManager.h"

void TitleScene::Initialize() {

	// カメラ初期化
	camera = std::make_unique<Camera>();
	camera->SetRotate({ cameraTransform.rotate });
	camera->SetTranslate({ cameraTransform.translate });

	// カメラマネージャ登録
	CameraManager::GetInstance()->AddCamera("main", camera.get());
	CameraManager::GetInstance()->SetActiveCamera("main");

	// 3Dオブジェクト
	object = std::make_unique <Object>();
	object->Initialize(camera.get());
	object->SetTranslate(objectPos);

	// 初期化済みの3Dオブジェクトにモデルを紐づける
	object->SetModel("plane.obj");

	// 音声再生
	//SoundManager::GetInstance()->Play("bgm");

}

void TitleScene::Update() {
	// 入力取得
	auto input = Input::GetInstance();
	// カメラ更新
	CameraManager::GetInstance()->Update();

	// * 3Dオブジェクト* //
	if (objectPos.x >= 3.0f)
		vector *= -1.0f;
	if (objectPos.x <= -3.0f)
		vector *= -1.0f;

	objectPos.x += vector;

	object->SetTranslate(objectPos);
	object->Update();

	if (input->TriggerKey(DIK_UP)) {
		if(effectType != 0)
			effectType--;

		// リセット
		isInversion = false;
		isGrayscale = false;
		isTwoColor = false;
		isRadialBlur = false;
		isDOF = false;
		isMotionBlur = false;
		isFullScreenCA = false;
		isVignette = false;
		isSpeedDistortion = false;
		isConcentrationLines = false;
		isPinch = false;
		isOutline = false;
		isBoxFilter = false;
		isDissolve = false;
		isRandomNoise = false;
	}
	if (input->TriggerKey(DIK_DOWN)) {
		if (effectType != 15)
			effectType++;

		// リセット
		isInversion = false;
		isGrayscale = false;
		isTwoColor = false;
		isRadialBlur = false;
		isDOF = false;
		isMotionBlur = false;
		isFullScreenCA = false;
		isVignette = false;
		isSpeedDistortion = false;
		isConcentrationLines = false;
		isPinch = false;
		isOutline = false;
		isBoxFilter = false;
		isDissolve = false;
		isRandomNoise = false;
	}

	if (effectType == 1)
		isInversion = true;
	else if (effectType == 2)
		isGrayscale = true;
	else if (effectType == 3) {
		isGrayscale = true;
		isTwoColor = true;
	}
	else if (effectType == 4)
		isRadialBlur = true;
	else if (effectType == 5)
		isDOF = true;
	else if (effectType == 6) {
		isMotionBlur = true;
		object->SetMotionBlur(true);
	}
	else if (effectType == 7)
		isFullScreenCA = true;
	else if (effectType == 8)
		isVignette = true;
	else if (effectType == 9)
		isSpeedDistortion = true;
	else if (effectType == 10)
		isConcentrationLines = true;
	else if (effectType == 11)
		isPinch = true;
	else if (effectType == 12)
		isOutline = true;
	else if (effectType == 13)
		isBoxFilter = true;
	else if (effectType == 14)
		isDissolve = true;
	else if (effectType == 15)
		isRandomNoise = true;

#pragma region ポストエフェクト
	// *ポストエフェクト* //
	PostEffect::GetInstance()->Update(camera.get());

	// 反転
	PostEffect::GetInstance()->SetInversion(isInversion);
	// グレースケール
	PostEffect::GetInstance()->SetGrayscale(isGrayscale);
	PostEffect::GetInstance()->SetTwoColor(isTwoColor);
	PostEffect::GetInstance()->SetThreshold(threshold);
	PostEffect::GetInstance()->SetContrast(contrast);
	// 放射線ブラー
	PostEffect::GetInstance()->SetRadialBlur(isRadialBlur);
	PostEffect::GetInstance()->SetBlurCenter(blurCenter);
	PostEffect::GetInstance()->SetBlurWidth(blurWidth);
	PostEffect::GetInstance()->SetBlurSamples(blurSamples);
	// ディスタンスフォグ
	PostEffect::GetInstance()->SetDistanceFog(isDistanceFog);
	PostEffect::GetInstance()->SetDistanceFogColor(distanceFogColor);
	PostEffect::GetInstance()->SetDistanceFogStart(distanceStart);
	PostEffect::GetInstance()->SetDistanceFogEnd(distanceEnd);
	// ハイトフォグ
	PostEffect::GetInstance()->SetHeightFog(isHeightFog);
	PostEffect::GetInstance()->SetHeightFogColor(heightFogColor);
	PostEffect::GetInstance()->SetHeightFogTop(heightFogTop);
	PostEffect::GetInstance()->SetHeightFogBottom(heightFogBottom);
	PostEffect::GetInstance()->SetHeightFogDensity(heightFogDensity);
	PostEffect::GetInstance()->HightFogUpdate(camera.get());
	// DOF
	PostEffect::GetInstance()->SetDOF(isDOF);
	PostEffect::GetInstance()->SetFocusDistance(focusDistance);
	PostEffect::GetInstance()->SetBokehRadius(bokehRadius);
	PostEffect::GetInstance()->SetFocusRange(focusRange);
	// ブルーム
	PostEffect::GetInstance()->SetBloomIntensity(bloomIntensity);
	PostEffect::GetInstance()->SetBloomThreshold(bloomThreshold);
	PostEffect::GetInstance()->SetBloomBlurRadius(bloomBlurRadius);
	// レンズフレア
	PostEffect::GetInstance()->SetLensFlare(isLensFlare);
	PostEffect::GetInstance()->SetLensFlareGhostCount(lensFlareGhostCount);
	PostEffect::GetInstance()->SetLensFlareHaloWidth(lensFlareHaloWidth);
	PostEffect::GetInstance()->SetIsACES(isACES);
	PostEffect::GetInstance()->SetCAIntensity(caIntensity);
	// モーションブラー
	PostEffect::GetInstance()->SetMotionBlur(isMotionBlur);
	PostEffect::GetInstance()->SetMotionBlurSamples(motionBlurSamples);
	PostEffect::GetInstance()->SetMotionBlurScale(motionBlurScale);
	// 色収差
	PostEffect::GetInstance()->SetFullScreenCA(isFullScreenCA);
	PostEffect::GetInstance()->SetFullScreenCAIntensity(fullScreenCAIntensity);
	// ビネット
	PostEffect::GetInstance()->SetVignette(isVignette);
	PostEffect::GetInstance()->SetVignetteIntensity(vignetteIntensity);
	PostEffect::GetInstance()->SetVignetteColor(vignetteColor);
	// スピードディストーション
	PostEffect::GetInstance()->SetSpeedDistortion(isSpeedDistortion);
	PostEffect::GetInstance()->SetSpeedDistortionStrength(strength);
	// 集中線
	PostEffect::GetInstance()->SetConcentrationLines(isConcentrationLines);
	PostEffect::GetInstance()->SetConcentrationLineIntensity(concentrationLineIntensity);
	PostEffect::GetInstance()->SetConcentrationLineCenter(concentrationLineCenter);
	PostEffect::GetInstance()->SetConcentrationLineDensity(concentrationLineDensity);
	PostEffect::GetInstance()->SetConcentrationLineLength(concentrationLineLength);
	PostEffect::GetInstance()->SetConcentrationLineSpeed(concentrationLineSpeed);
	// ピンチ
	PostEffect::GetInstance()->SetPinch(isPinch);
	PostEffect::GetInstance()->SetPinchStrength(pinchStrength);
	PostEffect::GetInstance()->SetPinchCenter(pinchCenter);
	PostEffect::GetInstance()->SetPinchRadius(pinchRadius);
	// アウトライン
	PostEffect::GetInstance()->SetOutline(isOutline);
	PostEffect::GetInstance()->SetOutlineThreshold(outlineThreshold);
	PostEffect::GetInstance()->SetOutlineColor(outlineColor);
	// 平滑化
	PostEffect::GetInstance()->SetBoxFilter(isBoxFilter);
	// ディゾルブ
	PostEffect::GetInstance()->SetDissolve(isDissolve);
	PostEffect::GetInstance()->SetDissolveThreshold(dissolveThreshold);
	PostEffect::GetInstance()->SetDissolveEdgeWidth(dissolveEdgeWidth);
	PostEffect::GetInstance()->SetDissolveNoiseScale(dissolveNoiseScale);
	PostEffect::GetInstance()->SetDissolveNoiseColor(dissolveNoiseColor);
	PostEffect::GetInstance()->SetDissolveEdgeColor(dissolveEdgeColor);
	// ランダムノイズ
	PostEffect::GetInstance()->SetRandomNoise(isRandomNoise);

#pragma endregion

#pragma region レイマーチング
	// レイマーチング
	RayMarching::GetInstance()->Update(camera.get());
	//rayMarching->SetTime(rayMarchingTime);
	RayMarching::GetInstance()->SetSunDir(rayMarchingSunDir);
	RayMarching::GetInstance()->SetCloudCoverage(rayMarchingCloudCoverage);
	RayMarching::GetInstance()->SetCloudTop(rayMarchingCloudBottom);
	RayMarching::GetInstance()->SetCloudBottom(rayMarchingCloudTop);
	RayMarching::GetInstance()->SetRialLight(rayMarchingIsRialLight);
	RayMarching::GetInstance()->SetAnimeLight(rayMarchingIsAnimeLight);
	RayMarching::GetInstance()->SetMotionBlur(rayMarchingIsMotionBlur);
	RayMarching::GetInstance()->SetCloudOpacity(rayMarchingCloudOpacity);
	RayMarching::GetInstance()->SetStorm(isStorm);
	RayMarching::GetInstance()->SetThunderFrequency(thunderFrequency);
	RayMarching::GetInstance()->SetThunderBrightness(thunderBrightness);


#pragma endregion

#ifdef USE_IMGUI
	// ImGui
	// フレームレートの取得と表示
	float fps = ImGui::GetIO().Framerate;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps, fps);

	ImGui::DragFloat3("cameraTranslate", &cameraTransform.translate.x, 0.1f, -500.0f, 500.0f);
	ImGui::DragFloat3("cameraRotate", &cameraTransform.rotate.x, 0.01f, -10.0f, 10.0f);
	camera->SetTranslate(cameraTransform.translate);
	camera->SetRotate(cameraTransform.rotate);

#pragma region ポストエフェクト
	// *ポストエフェクト* //
	ImGui::Text("PostEffect"); // ポストエフェクトのテキスト

	// 反転
	if (ImGui::TreeNode("inversion")) {
		ImGui::Checkbox("OnOff", &isInversion);

		ImGui::TreePop();
	}
	// グレースケール
	if (ImGui::TreeNode("grayscale")) {
		ImGui::Checkbox("OnOff", &isGrayscale);

		ImGui::TreePop();
	}
	// 放射線ブラー
	if (ImGui::TreeNode("radialBlur")) {
		ImGui::Checkbox("OnOff", &isRadialBlur);

		if (isRadialBlur) {
			ImGui::DragFloat2("blurCenter", &blurCenter.x, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("blurWidth", &blurWidth, 0.001f, 0.0f, 0.1f);
			ImGui::DragInt("blurSamples", &blurSamples, 1, 1, 100);
		}

		ImGui::TreePop();
	}
	// ディスタンスフォグ
	if (ImGui::TreeNode("distanceFog")) {
		ImGui::Checkbox("OnOff", &isDistanceFog);

		if (isDistanceFog) {
			ImGui::ColorEdit3("fogColor", &distanceFogColor.x);
			ImGui::DragFloat("fogStart", &distanceStart, 0.1f, 0.0f, 100.0f);
			ImGui::DragFloat("fogEnd", &distanceEnd, 0.1f, 0.0f, 100.0f);
		}

		ImGui::TreePop();
	}
	// ハイトフォグ
	if (ImGui::TreeNode("heightFog")) {
		ImGui::Checkbox("OnOff", &isHeightFog);

		if (isHeightFog) {
			ImGui::ColorEdit3("heightFogColor", &heightFogColor.x);
			ImGui::DragFloat("heightFogTop", &heightFogTop, 0.1f, -100.0f, 100.0f);
			ImGui::DragFloat("heightFogBottom", &heightFogBottom, 0.1f, -100.0f, 100.0f);
			ImGui::DragFloat("heightFogDensity", &heightFogDensity, 0.01f, 0.0f, 10.0f);
		}

		ImGui::TreePop();
	}
	// DOF
	if (ImGui::TreeNode("DOF")) {
		ImGui::Checkbox("OnOff", &isDOF);

		if (isDOF) {
			ImGui::DragFloat("focusDistance", &focusDistance, 0.1f, 0.0f, 100.0f);
			ImGui::DragFloat("bokehRadius", &bokehRadius, 0.1f, 0.0f, 100.0f);
			ImGui::DragFloat("focusRange", &focusRange, 0.1f, 0.0f, 100.0f);
		}

		ImGui::TreePop();
	}
	// ブルーム
	if (ImGui::TreeNode("Bloom")) {
		ImGui::DragFloat("bloomThreshold", &bloomThreshold, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat("bloomIntensity", &bloomIntensity, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat("bloomRadius", &bloomBlurRadius, 0.01f, 0.0f, 10.0f);

		ImGui::TreePop();
	}
	// レンズフレア
	if (ImGui::TreeNode("LensFlare")) {
		ImGui::Checkbox("OnOff", &isLensFlare);

		if (isLensFlare) {
			ImGui::DragInt("lensFlareGhostCount", &lensFlareGhostCount, 1, 0,10);
			ImGui::DragFloat("lensFlareHaloWidth", &lensFlareHaloWidth, 0.01f, 0.0f, 10.0f);
			ImGui::Checkbox("isACES", &isACES);
			ImGui::DragFloat("caIntensity", &caIntensity, 0.001f, 0.0f, 10.0f);
		}
		ImGui::Text("%.3f", PostEffect::GetInstance()->GetLensFlareGhostDispersal());

		ImGui::TreePop();
	}
	// モーションブラー
	if (ImGui::TreeNode("MotionBlur")) {
		ImGui::Checkbox("OnOff", &isMotionBlur);

		if (isLensFlare) {
			ImGui::DragInt("motionBlurSamples", &motionBlurSamples, 1, 0, 20);
			ImGui::DragFloat("motionBlurScale", &motionBlurScale, 0.01f, 0.0f, 10.0f);
		}

		ImGui::TreePop();
	}
	// 色収差
	if (ImGui::TreeNode("CA")) {
		ImGui::Checkbox("OnOff", &isFullScreenCA);
		
		if (isFullScreenCA)
		ImGui::DragFloat("fullScreenCAIntensity", &fullScreenCAIntensity, 0.001f, 0.0f, 10.0f);
		
		ImGui::TreePop();
	}
	// ビネット
	if (ImGui::TreeNode("Vignette")) {
		ImGui::Checkbox("OnOff", &isVignette);
		if (isVignette) {
			ImGui::DragFloat("vignetteIntensity", &vignetteIntensity, 0.01f, 0.0f, 1.0f);
			ImGui::ColorEdit3("vignetteColor", &vignetteColor.x);
		}
		ImGui::TreePop();
	}
	// スピードディストーション
	if (ImGui::TreeNode("SpeedDistortion")) {
		ImGui::Checkbox("OnOff", &isSpeedDistortion);
		if (isSpeedDistortion) {
			ImGui::DragFloat("strength", &strength, 0.01f, 0.0f, 1.0f);
		}
		ImGui::TreePop();
	}
	// 集中線
	if (ImGui::TreeNode("ConcentrationLines")) {
		ImGui::Checkbox("OnOff", &isConcentrationLines);
		if (isConcentrationLines) {
			ImGui::DragFloat("concentrationLineIntensity", &concentrationLineIntensity, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat2("concentrationLineCenter", &concentrationLineCenter.x, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("concentrationLineDensity", &concentrationLineDensity, 1.0f, 0.0f, 500.0f);
			ImGui::DragFloat("concentrationLineLength", &concentrationLineLength, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("concentrationLineSpeed", &concentrationLineSpeed, 0.1f, 0.0f, 100.0f);
		
		}
		ImGui::TreePop();
	}
	// ピンチエフェクト
	if (ImGui::TreeNode("Pinch")) {
		ImGui::Checkbox("OnOff", &isPinch);
		if (isPinch) {
			ImGui::DragFloat("pinchStrength", &pinchStrength, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat2("pinchCenter", &pinchCenter.x, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("pinchRadius", &pinchRadius, 0.01f, 0.0f, 10.0f);
			
		}
		ImGui::TreePop();
	}
	// アウトライン
	if (ImGui::TreeNode("Outline")) {
		ImGui::Checkbox("OnOff", &isOutline);
		if (isOutline) {
			ImGui::DragFloat("outlineThreshold", &outlineThreshold, 0.0001f, 0.0f, 0.05f);
			ImGui::ColorEdit4("outlineColor", &outlineColor.x);
		}
		ImGui::TreePop();
	}
	// 平滑化
	if (ImGui::TreeNode("BoxFilter")) {
		ImGui::Checkbox("OnOff", &isBoxFilter);
		ImGui::TreePop();
	}
	// ディゾルブ
	if (ImGui::TreeNode("Dissolve")) {
		ImGui::Checkbox("OnOff", &isDissolve);
		if (isDissolve) {
			ImGui::DragFloat("dissolveThreshold", &dissolveThreshold, 0.01f, 0.0f, 10.0f);
			ImGui::DragFloat("dissolveEdgeWidth", &dissolveEdgeWidth,0.001f,0.0f,1.0f);
			ImGui::DragFloat("dissolveNoiseScale", &dissolveNoiseScale,0.1f,0.0f,50.0f);
			ImGui::ColorEdit3("dissolveNoiseColor", &dissolveNoiseColor.x);
			ImGui::ColorEdit3("dissolveEdgeColor", &dissolveEdgeColor.x);
		}
		ImGui::TreePop();
	}
	// ランダムノイズ
	if (ImGui::TreeNode("RandomNoise")) {
		ImGui::Checkbox("OnOff", &isRandomNoise);
		ImGui::TreePop();
	}

#pragma endregion

#pragma region レイマーチング

	// レイマーチング
	//ImGui::DragFloat("rayMarchingTime", &rayMarchingTime, 0.1f,0.0f,10.0f);
	ImGui::DragFloat3("rayMarchingSunDir", &rayMarchingSunDir.x, 0.01f,-1.0f,1.0f);
	ImGui::DragFloat("rayMarchingCloudCoverage", &rayMarchingCloudCoverage, 0.01f,-5.0f,10.0f);
	ImGui::DragFloat("rayMarchingCloudBottom", &rayMarchingCloudBottom, 10.0f,-5000.0f,5000.0f);
	ImGui::DragFloat("rayMarchingCloudTop", &rayMarchingCloudTop, 10.0f, -5000.0f, 5000.0f);
	ImGui::Checkbox("rayMarchingIsRialLight", &rayMarchingIsRialLight);
	ImGui::Checkbox("rayMarchingIsAnimeLight", &rayMarchingIsAnimeLight);
	ImGui::Checkbox("rayMarchingIsMotionBlur", &rayMarchingIsMotionBlur);
	ImGui::DragFloat("rayMarchingCloudOpacity", &rayMarchingCloudOpacity, 0.001f, 0.0f, 0.1f);
	ImGui::Checkbox("isStorm", &isStorm);
	ImGui::DragFloat("thunderFrequency", &thunderFrequency, 0.001f, 0.0f, 10.0f);
	ImGui::DragFloat("thunderBrightness", &thunderBrightness, 0.01f, 0.0f, 300.0f);

#pragma endregion

#endif

}

void TitleScene::Draw2D() {
	// 2Dオブジェクトの描画準備
	SpriteCommon::GetInstance()->SetCommonPipelineState();

	// スプライト描画
	//sprite->Draw();
}
void TitleScene::Draw3D() {
	// 3Dオブジェクトの描画準備
	ObjectCommon::GetInstance()->SetCommonPipelineState();

	
	// 3Dオブジェクト描画
	object->Draw();


	// アウトライン描画準備
	ObjectCommon::GetInstance()->SetOutlinePipelineState();

	
}

void TitleScene::Finalize() {
	CameraManager::GetInstance()->RemoveCamera("main");
}
